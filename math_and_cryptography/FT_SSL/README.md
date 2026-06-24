_this project is made by csalamit_

# ft_ssl

A partial reimplementation of `openssl` in C, supporting MD5 and SHA-256 digest commands with flags compatible with the original tool.

```
./ft_ssl md5 [-p] [-q] [-r] [-s string] [file ...]
./ft_ssl sha256 [-p] [-q] [-r] [-s string] [file ...]
```

---

## Allowed functions

`open` `close` `read` `write` `malloc` `free` — and any custom utility whose implementation relies only on the above.

---

## Flags

| Flag | Behaviour |
|------|-----------|
| `-p` | Echo stdin to stdout, then append the checksum |
| `-q` | Quiet mode — print the hash only, no label |
| `-r` | Reverse output format: hash first, then filename |
| `-s <string>` | Print the hash of the given string |

Flags can be combined (e.g. `-qr`). Without any flag or file, the program reads from stdin.

---

## MD5

[RFC 1321](https://datatracker.ietf.org/doc/html/rfc1321)

MD5 produces a 128-bit (16-byte) digest from an arbitrarily long input.
The algorithm works in four stages:

1. **Initialisation** — four 32-bit state variables `A B C D` are set to fixed magic constants.
2. **Padding** — the message is extended to a length that is a multiple of 512 bits: a `1` bit is appended, followed by `0` bits, followed by the original length encoded on 64 bits (little-endian).
3. **Block processing** — the padded message is split into 512-bit blocks. Each block runs through 64 operations organised in 4 rounds of 16, using the non-linear functions `F G H I` and per-step rotation constants from tables `T` and `S`.
4. **Digest** — the final values of `A B C D` are concatenated in little-endian byte order to produce the 128-bit hash.

### Why hardcoded shift tables (`S`) over dynamic formulas?

During development we experimented with replacing the static shift array `S` (rotation distances) with a computed formula to reduce magic constants in the source. We reverted to the static table for four reasons:

**1 — Avalanche effect preservation.**
The 16 shift values (`7 12 17 22`, `5 9 14 20`, `4 11 16 23`, `6 10 15 21`) were chosen by Ronald Rivest and are mathematically optimised to maximise diffusion. A single bit change in the input must cascade unpredictably through the entire state — these specific distances are what achieve that.

**2 — Fragility of arithmetic approximations.**
Any attempt to reproduce the irregular pattern via modulo or conditional arithmetic introduces operator-precedence risk. A single wrong constant silently produces a completely different hash — including breaking the canonical empty-string test vector `d41d8cd98f00b204e9800998ecf8427e`.

**3 — Zero-overhead access.**
The array lives in `.rodata` and is fetched in O(1) with no computation. Recomputing the shift distance on each of the 64 iterations per block adds latency for no gain.

**4 — Auditability.**
A literal table can be verified against RFC 1321 line by line. A formula cannot.

### Round structure

Each of the 64 steps follows the pattern shown in RFC 1321 as `[ABCD k s i]`:

```
Round 1 (F):  [ABCD 0  7  1]  [DABC 1 12  2]  [CDAB 2 17  3]  [BCDA 3 22  4]  ...
Round 2 (G):  [ABCD 1  5 17]  [DABC 6  9 18]  [CDAB 11 14 19] [BCDA 0 20 20]  ...
Round 3 (H):  [ABCD 5  4 33]  [DABC 8 11 34]  [CDAB 11 16 35] [BCDA 14 23 36] ...
Round 4 (I):  [ABCD 0  6 49]  [DABC 7 10 50]  [CDAB 14 15 51] [BCDA 5 21 52]  ...
```

`k` = index into the 16-word message block, `s` = rotation distance from `S[]`, `i` = index into the sine-derived constant table `T[]`.

### Test vectors

```
echo -n ""       | ./ft_ssl md5   -> d41d8cd98f00b204e9800998ecf8427e
echo -n "abc"    | ./ft_ssl md5   -> 900150983cd24fb0d6963f7d28e17f72
echo -n "hello"  | ./ft_ssl md5   -> 5d41402abc4b2a76b9719d911017c592
```

---

## SHA-256

[RFC 6234](https://datatracker.ietf.org/doc/html/rfc6234)

SHA-256 produces a 256-bit (32-byte) digest. It shares the same padding scheme as MD5 (with the length encoded in **big-endian** this time) but differs in every other aspect:

- **8 state variables** `a b c d e f g h` initialised from the fractional parts of the square roots of the first 8 primes.
- **64 rounds** per 512-bit block (vs 64 operations split into 4 rounds in MD5).
- **Non-linear functions** `Ch`, `Maj`, `Σ0`, `Σ1`, `σ0`, `σ1` built from bitwise rotations and XOR.
- **64 round constants** `K[0..63]` derived from the cube roots of the first 64 primes.
- Output is written **big-endian**, unlike MD5's little-endian.

### Test vectors

```
echo -n ""      | ./ft_ssl sha256 -> e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
echo -n "abc"   | ./ft_ssl sha256 -> ba7816bf8f01cfea414140de5dae2ec73b00361bbef0469f628b4bfe6a1c1e4c9
echo -n "hello" | ./ft_ssl sha256 -> 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
```

---

## Project structure

```
ft_ssl/
├── include/
│   └── ft_ssl.h
└── source/
    ├── main.c       — argument parsing, flag handling, dispatch
    ├── md5.c        — padding + ft_md5_algo
    ├── sha256.c     — padding + ft_sha256_algo
    └── utils.c      — ft_strlen, ft_memcpy, ft_calloc, ft_realloc,
                       ft_strcmp, ft_error, ft_printf_hex, ft_sin, ft_fabs
```

---

## Building

```bash
make
./ft_ssl md5 -s "hello"
./ft_ssl md5 Makefile
echo "test" | ./ft_ssl sha256 -p
```