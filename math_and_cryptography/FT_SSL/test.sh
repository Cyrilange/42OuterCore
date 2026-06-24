#!/bin/bash

echo "=== setup ==="
echo "hello world" > /tmp/test1.txt
echo "42 is nice" > /tmp/test2.txt
echo "https://www.42.fr/" > website
echo "And above all," > file

echo "=== md5 files ==="
valgrind ./ft_ssl md5 /tmp/test1.txt
valgrind ./ft_ssl md5 /tmp/test2.txt
valgrind ./ft_ssl md5 -r /tmp/test1.txt
valgrind ./ft_ssl md5 -q /tmp/test1.txt

echo "=== sha256 files ==="
valgrind ./ft_ssl sha256 /tmp/test1.txt
valgrind ./ft_ssl sha256 /tmp/test2.txt
valgrind ./ft_ssl sha256 -r /tmp/test1.txt
valgrind ./ft_ssl sha256 -q /tmp/test1.txt

echo "=== edge cases ==="
valgrind ./ft_ssl md5 /tmp/inexistant.txt
valgrind ./ft_ssl md5 /dev/null
valgrind ./ft_ssl sha256 /dev/null

echo "=== strings ==="
valgrind ./ft_ssl md5 -s "42 is nice"
valgrind ./ft_ssl md5 -s -r "42 is nice"
valgrind ./ft_ssl md5 -s -q "42 is nice"
valgrind ./ft_ssl sha256 -s "42 is nice"
valgrind ./ft_ssl sha256 -s -r "42 is nice"
valgrind ./ft_ssl sha256 -s -q "42 is nice"

echo "=== flag -p ==="
echo "42 is nice" | valgrind ./ft_ssl md5 -p
echo "42 is nice" | valgrind ./ft_ssl md5 -p -q
echo "42 is nice" | valgrind ./ft_ssl md5 -p -r
echo "42 is nice" | valgrind ./ft_ssl md5 -p -s "hello"
echo "42 is nice" | valgrind ./ft_ssl sha256 -p
echo "42 is nice" | valgrind ./ft_ssl sha256 -p -q
echo "42 is nice" | valgrind ./ft_ssl sha256 -p -r
echo "42 is nice" | valgrind ./ft_ssl sha256 -p -s "hello"

echo "=== subject tests ==="
valgrind ./ft_ssl sha256 -q website
echo "expected: 1ceb55d2845d9dd98557b50488db12bbf51aaca5aa9c1199eb795607a2457daf"
sha256sum website

valgrind ./ft_ssl sha256 -s "42 is nice"
echo "expected: SHA256 (\"42 is nice\") = b7e44c7a40c5f80139f0a50f3650fb2bd8d00b0d24667c4c2ca32c88e13b758f"
echo -n "42 is nice" | sha256sum

echo "42 is nice" | valgrind ./ft_ssl md5
echo "expected: (stdin)= 35f1d6de0302e2086a4e472266efb3a9"
echo "42 is nice" | md5sum

echo "42 is nice" | valgrind ./ft_ssl md5 -p
echo "expected: (\"42 is nice\")= 35f1d6de0302e2086a4e472266efb3a9"

echo "Pity the living." | valgrind ./ft_ssl md5 -q -r
echo "expected: e20c3b973f63482a778f3fd1869b7f25"

valgrind ./ft_ssl md5 file
echo "expected: MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"

valgrind ./ft_ssl md5 -r file
echo "expected: 53d53ea94217b259c11a5a2d104ec58a file"

valgrind ./ft_ssl md5 -s "pity those that aren't following baerista on spotify."
echo "expected: MD5 (\"pity those that aren't following baerista on spotify.\") = a3c990a1964705d9bf0e602f44572f5f"

echo "be sure to handle edge cases carefully" | valgrind ./ft_ssl md5 -p file
echo "expected: (\"be sure to handle edge cases carefully\")= 3553dc7dc5963b583c056d1b9fa3349c"
echo "expected: MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"

echo "some of this will not make sense at first" | valgrind ./ft_ssl md5 file
echo "expected: MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"

echo "but eventually you will understand" | valgrind ./ft_ssl md5 -p -r file
echo "expected: (\"but eventually you will understand\")= dcdd84e0f635694d2a943fa8d3905281"
echo "expected: 53d53ea94217b259c11a5a2d104ec58a file"

echo "GL HF let's go" | valgrind ./ft_ssl md5 -p -s "foo" file
echo "expected: (\"GL HF let's go\")= d1e3cc342b6da09480b27ec57ff243e2"
echo "expected: MD5 (\"foo\") = acbd18db4cc2f85cedef654fccc4a4d8"
echo "expected: MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"

echo "one more thing" | valgrind ./ft_ssl md5 -r -p -s "foo" file -s "bar"
echo "expected: (\"one more thing\")= a0bd1876c6f011dd50fae52827f445f5"
echo "expected: acbd18db4cc2f85cedef654fccc4a4d8 \"foo\""
echo "expected: 53d53ea94217b259c11a5a2d104ec58a file"
echo "expected: ft_ssl: md5: -s: No such file or directory"
echo "expected: ft_ssl: md5: bar: No such file or directory"

echo "just to be extra clear" | valgrind ./ft_ssl md5 -r -q -p -s "foo" file
echo "expected: just to be extra clear"
echo "expected: 3ba35f1ea0d170cb3b9a752e3360286c"
echo "expected: acbd18db4cc2f85cedef654fccc4a4d8"
echo "expected: 53d53ea94217b259c11a5a2d104ec58a"

echo "=== reference checksums ==="
md5sum /tmp/test1.txt
md5sum /tmp/test2.txt
sha256sum /tmp/test1.txt
sha256sum /tmp/test2.txt
echo -n "42 is nice" | md5sum
echo -n "42 is nice" | sha256sum
echo -n "hello" | md5sum
echo -n "hello" | sha256sum