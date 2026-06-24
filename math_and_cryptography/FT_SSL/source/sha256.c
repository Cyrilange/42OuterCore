/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalamit <csalamit@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:46:46 by csalamit          #+#    #+#             */
/*   Updated: 2026/06/03 16:16:05 by csalamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/ft_ssl.h"  

static const uint32_t g_k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
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
	int i = 0;
	while (i < 8) {
		padded_msg[*new_size - 8 + i] = (bits_size >> (56 - i * 8)) & 0xff;
		i++;
	}
	return (padded_msg);
}

void ft_sha256_algo(const unsigned char *message, size_t len, unsigned char *digest) {
	uint32_t h0 = 0x6a09e667;
	uint32_t h1 = 0xbb67ae85;
	uint32_t h2 = 0x3c6ef372;
	uint32_t h3 = 0xa54ff53a;
	uint32_t h4 = 0x510e527f;
	uint32_t h5 = 0x9b05688c;
	uint32_t h6 = 0x1f83d9ab;
	uint32_t h7 = 0x5be0cd19;

	unsigned char *padded; size_t padded_len, offset;

	padded = ft_padding(message, len, &padded_len);
	if (!padded) {return ;}
	offset = 0;
	while (offset < padded_len) {
	uint32_t w[64];
	uint32_t a, b, c, d, e, f, g, h;
	uint32_t t1, t2;
	int i = 0;
	while (i < 16) {
	w[i] = ((uint32_t)padded[offset + i * 4] << 24) |
	((uint32_t)padded[offset + i * 4 + 1] << 16) |
	((uint32_t)padded[offset + i * 4 + 2] << 8) |
	((uint32_t)padded[offset + i * 4 + 3]);
	i++;
	}
	while (i < 64) { w[i] = sig1(w[i - 2]) + w[i - 7] + sig0(w[i - 15])	+ w[i - 16]; i++;}

	a = h0;
	b = h1;
	c = h2;
	d = h3;
	e = h4;
	f = h5;
	g = h6;
	h = h7;
	i = 0;
	while (i < 64) { t1 = h + SIG1(e) + CH(e, f, g) + g_k[i] + w[i]; 
	t2 = SIG0(a) + MAJ(a, b, c);
	h = g;
	g = f;
	f = e;
	e = d + t1;
	d = c;
	c = b;
	b = a;
	a = t1 + t2;
	i++; }

	h0 += a;
	h1 += b;
	h2 += c;
	h3 += d;
	h4 += e;
	h5 += f;
	h6 += g;
	h7 += h;

	offset += 64;
	}

	free(padded);

	/* digest big-endian */
	uint32_t hash[8] = { h0, h1, h2, h3, h4, h5, h6, h7 };
	for (int i = 0; i < 8; i++) {
	digest[i * 4]     = (hash[i] >> 24) & 0xff;
	digest[i * 4 + 1] = (hash[i] >> 16) & 0xff;
	digest[i * 4 + 2] = (hash[i] >> 8) & 0xff;
	digest[i * 4 + 3] = hash[i] & 0xff;
	}
}