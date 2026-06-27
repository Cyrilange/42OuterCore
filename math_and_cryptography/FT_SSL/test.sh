#!/bin/bash

FT_SSL=${1:-./ft_ssl}
TMP_DIR=$(mktemp -d)
PASS=0
FAIL=0

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

title() {
	echo ""
	echo -e "${BLUE}=== $1 ===${NC}"
}

check_diff() {
	local label="$1"
	local file_a="$2"
	local file_b="$3"

	if diff -q "$file_a" "$file_b" > /dev/null 2>&1; then
		echo -e "${GREEN}[OK]${NC} $label"
		PASS=$((PASS+1))
	else
		echo -e "${RED}[FAIL]${NC} $label"
		echo "   --- expected ---"
		sed 's/^/   /' "$file_a"
		echo "   --- got ---"
		sed 's/^/   /' "$file_b"
		FAIL=$((FAIL+1))
	fi
}

check_nonempty() {
	local label="$1"
	local file="$2"

	if [ -s "$file" ]; then
		echo -e "${GREEN}[OK]${NC} $label"
		PASS=$((PASS+1))
	else
		echo -e "${RED}[FAIL]${NC} $label"
		FAIL=$((FAIL+1))
	fi
}

if [ ! -x "$FT_SSL" ]; then
	echo -e "${RED}Error: $FT_SSL not found or not executable.${NC}"
	exit 1
fi

echo -e "${YELLOW}Binary tested: $FT_SSL${NC}"
echo -e "${YELLOW}Temp directory: $TMP_DIR${NC}"

FILE="$TMP_DIR/file"
IPSUM="$TMP_DIR/some_ipsum"

echo 'is md5("salt") a salted hash?' > "$FILE"
echo "Lorem ipsum dolor amet thundercats letterpress cray portland cornhole" > "$IPSUM"

title "1. General behavior"

"$FT_SSL" > "$TMP_DIR/no_args.out" 2>&1
check_nonempty "Run with no arguments" "$TMP_DIR/no_args.out"

"$FT_SSL" foo > "$TMP_DIR/bad_cmd.out" 2>&1
check_nonempty "Invalid command" "$TMP_DIR/bad_cmd.out"

title "2. Command dispatcher"
echo "Check manually in the source code (0 to 5)"

title "3. MD5 - correctness"

"$FT_SSL" md5 "$FILE" > "$TMP_DIR/md5_ftssl.out" 2>&1
md5sum --tag "$FILE" > "$TMP_DIR/md5_ref.out" 2>&1
check_diff "md5 == md5sum --tag" "$TMP_DIR/md5_ref.out" "$TMP_DIR/md5_ftssl.out"

title "4. Flag -q (md5)"

md5sum "$FILE" | awk '{print $1}' > "$TMP_DIR/hash_1"
"$FT_SSL" md5 -q "$FILE" > "$TMP_DIR/hash_2"
check_diff "md5 -q" "$TMP_DIR/hash_1" "$TMP_DIR/hash_2"

title "5. Flags -r and -s (md5)"

md5sum "$FILE" > "$TMP_DIR/md5_r_ref.out"
"$FT_SSL" md5 -r "$FILE" > "$TMP_DIR/md5_r_ftssl.out"
check_diff "md5 -r" "$TMP_DIR/md5_r_ref.out" "$TMP_DIR/md5_r_ftssl.out"

"$FT_SSL" md5 -s "pity those that aren't following baerista on spotify."

title "6. Flag -p (md5)"

VAR="Magic mirror on the wall, think I wanna smash them all?"

echo "$VAR" | md5sum | awk -v var="$VAR" '{print var " " $1}' > "$TMP_DIR/p_ref.out"
echo "$VAR" | "$FT_SSL" md5 -p > "$TMP_DIR/p_ftssl.out"
check_diff "md5 -p" "$TMP_DIR/p_ref.out" "$TMP_DIR/p_ftssl.out"

title "7. SHA256 - correctness"

openssl sha256 "$IPSUM" | awk '{print $2}' > "$TMP_DIR/sha_ref.out"
"$FT_SSL" sha256 -q "$IPSUM" > "$TMP_DIR/sha_ftssl.out"
check_diff "sha256 -q == openssl" "$TMP_DIR/sha_ref.out" "$TMP_DIR/sha_ftssl.out"

title "8. Flags -q / -r / -s / -p with SHA256"

sha256sum "$IPSUM" | awk '{print $1}' > "$TMP_DIR/sha256_q_ref.out"
"$FT_SSL" sha256 -q "$IPSUM" > "$TMP_DIR/sha256_q_ftssl.out"
check_diff "sha256 -q" "$TMP_DIR/sha256_q_ref.out" "$TMP_DIR/sha256_q_ftssl.out"

sha256sum "$IPSUM" > "$TMP_DIR/sha256_r_ref.out"
"$FT_SSL" sha256 -r "$IPSUM" > "$TMP_DIR/sha256_r_ftssl.out"
check_diff "sha256 -r" "$TMP_DIR/sha256_r_ref.out" "$TMP_DIR/sha256_r_ftssl.out"

echo "$VAR" | sha256sum | awk -v var="$VAR" '{print var " " $1}' > "$TMP_DIR/sha256_p_ref.out"
echo "$VAR" | "$FT_SSL" sha256 -p > "$TMP_DIR/sha256_p_ftssl.out"
check_diff "sha256 -p" "$TMP_DIR/sha256_p_ref.out" "$TMP_DIR/sha256_p_ftssl.out"

"$FT_SSL" sha256 -s "pity those that aren't following baerista on spotify."

title "SUMMARY"
echo -e "${GREEN}Passed: $PASS${NC}"
echo -e "${RED}Failed: $FAIL${NC}"

rm -rf "$TMP_DIR"