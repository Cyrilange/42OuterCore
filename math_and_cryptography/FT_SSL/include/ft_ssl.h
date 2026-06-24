#ifndef FT_SSL_H
# define FT_SSL_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>

/* Pi constant used to generate the MD5 sine-based table T[i] */
#define FT_PI 3.14159265358979323846
/* --- MD5 ----------------------------------------------------------------- */
/* Round 1: if X then Y else Z */
#define F(X, Y, Z) ((X & Y) | (~X & Z))
/* Round 2: if Z then X else Y */
#define G(X, Y, Z) ((X & Z) | (Y & ~Z))
/* Round 3: bitwise XOR of all three — parity function */
#define H(X, Y, Z) (X ^ Y ^ Z)
/* Round 4: Y XOR (X OR NOT Z) */
#define I(X, Y, Z) (Y ^ (X | ~Z))
/* Left circular rotation of x by n bits on a 32-bit word */
#define LEFT_ROTATE(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
/* --- SHA-256 ------------------------------------------------------------- */
/* Choose: for each bit, x selects between y (bit=1) and z (bit=0) */
#define CH(x, y, z)  ((x & y) ^ (~x & z))
/* Majority: returns 1 if at least two of x, y, z have that bit set */
#define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
/* Right circular rotation of x by n bits on a 32-bit word */
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
/* Capital Sigma 0: applied to state variable a each round */
#define SIG0(x) (ROTR(x, 2)  ^ ROTR(x, 13) ^ ROTR(x, 22))
/* Capital Sigma 1: applied to state variable e each round */
#define SIG1(x) (ROTR(x, 6)  ^ ROTR(x, 11) ^ ROTR(x, 25))
/* Lowercase sigma 0: used in the message schedule to expand W[i] */
#define sig0(x) (ROTR(x, 7)  ^ ROTR(x, 18) ^ ((x) >> 3))
/* Lowercase sigma 1: used in the message schedule to expand W[i] */
#define sig1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ ((x) >> 10))

typedef struct s_flags {
    int   p; // -p : echo STDIN to STDOUT and append checksum
    int   q; // -q : quiet mode
    int   r; // -r : reverse the format of the output
    int   s; // -s : print the sum of the given string
   // char  *s_arg; // Stocke char that follow   -s
} t_flags;


/*
---------UTILS
*/

void ft_error(char *str);
size_t ft_strlen(char *str);
int ft_strcmp(const char *s1, const char *s2);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_calloc(size_t count, size_t size);
double ft_fabs(double x);
double ft_sin(double x);
void ft_printf_hex(unsigned char byte);
unsigned char   *read_fd(int fd, size_t *out_len);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	print_flag(t_flags f, char *algo, unsigned char *d, int len, char *str, int is_file);

/*
--------md5
*/

void ft_md5_algo(const unsigned char *message, size_t len, unsigned char *digest);

/*
----------sha256
*/

void	ft_sha256_algo(const unsigned char *message, size_t len, unsigned char *digest);

#endif