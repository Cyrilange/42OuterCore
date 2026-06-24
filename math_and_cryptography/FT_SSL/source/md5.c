/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalamit <csalamit@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:46:41 by csalamit          #+#    #+#             */
/*   Updated: 2026/06/03 12:04:58 by csalamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"


/*
    ** Table T: 64-element table constructed from a sine function.
    ** T[i] = floor(4294967296 * abs(sin(i))), where i is in radians.
    ** Index 0 is unused (set to 0) to match the 1-to-64 indexing of the RFC.
    */
 static  const uint32_t T[] = {
	0, /* Unused padding index */
	
	/* Round 1 (Steps 1 to 16) */
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,

	/* Round 2  (Steps 17 to 32) */
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,

	/* Round 3  (Steps 33 to 48) */
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,

	/* Round 4  (Steps 49 to 64) */
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};
static const int S[] = {
	0,
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22, // Round 1
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, // Round 2
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, // Round 3
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21  // Round 4
};


static unsigned char	*ft_padding(const unsigned char *message, size_t original_size, size_t *new_size)
{
	uint64_t		bits_size;
	unsigned char	*padded_msg;

	*new_size = ((original_size + 9 + 63) / 64) * 64;
	padded_msg = ft_calloc(*new_size, sizeof(unsigned char));
	if (!padded_msg)
		return (NULL);
	if (message && original_size > 0)
		ft_memcpy(padded_msg, message, original_size);
	padded_msg[original_size] = 0x80;
	bits_size = (uint64_t)original_size * 8;
	ft_memcpy(padded_msg + *new_size - 8, &bits_size, sizeof(uint64_t));
	return (padded_msg);
}


void	ft_md5_algo(const unsigned char *message, size_t len, unsigned char *digest) {
	size_t			offset = 0;
	size_t			new_size = 0;
	unsigned char	*padding;
	uint32_t		A = 0x67452301;
	uint32_t		B = 0xefcdab89;
	uint32_t		C = 0x98badcfe;
	uint32_t		D = 0x10325476;

	
	padding = ft_padding(message, len, &new_size);
	if (!padding)
		return ;


	while (offset < new_size)
	{
		unsigned char	*block = padding + offset;
		uint32_t		*X = (uint32_t *)block;
		uint32_t		a = A;
		uint32_t		b = B;
		uint32_t		c = C;
		uint32_t		d = D;
		int				i;
		uint32_t		f;
		uint32_t		g;

		i = 1;
		while (i <= 64)
		{
			if (i <= 16)
			{
				f = F(b, c, d);
				g = (i - 1) % 16;
			}
			else if (i <= 32)
			{
				f = G(b, c, d);
				g = (5 * (i - 1) + 1) % 16;
			}
			else if (i <= 48)
			{
				f = H(b, c, d);
				g = (3 * (i - 1) + 5) % 16;
			}
			else
			{
				f = I(b, c, d);
				g = (7 * (i - 1)) % 16;
			}
			uint32_t temp = b + LEFT_ROTATE(a + f + X[g] + T[i], S[i]);
			a = d;
			d = c;
			c = b;
			b = temp;
			i++;
		}
		A += a;
		B += b;
		C += c;
		D += d;
		offset += 64;
	}
	ft_memcpy(digest, &A, 4);
	ft_memcpy(digest + 4, &B, 4);
	ft_memcpy(digest + 8, &C, 4);
	ft_memcpy(digest + 12, &D, 4);
	free(padding);
}