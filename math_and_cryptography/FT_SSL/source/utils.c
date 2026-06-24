/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalamit <csalamit@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:27:11 by csalamit          #+#    #+#             */
/*   Updated: 2026/06/04 18:20:01 by csalamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

size_t ft_strlen(char *str) {
	size_t i = 0;
	while(str[i] != '\0') {
		i++;
	}
	return i;
}

void ft_error(char *str) {
	write(2, str , ft_strlen(str));
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t              i;
	unsigned char       *d;
	const unsigned char *s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void *ft_calloc(size_t count, size_t size)
{
	void            *ptr;
	size_t          total_size;
	size_t          i;
	unsigned char   *p;

	total_size = count * size;

	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);

	p = (unsigned char *)ptr;
	i = 0;
	while (i < total_size)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}

double ft_fabs(double x) {
    if (x < 0)
        return (-x);
    return (x);
}



double ft_sin(double x) {
    double term;
    double sum;
    int    i;

    term = x;
    sum = x;
    i = 1;
    while (i < 15)
    {
        term = -term * x * x / ((2 * i) * (2 * i + 1));
        sum += term;
        i++;
    }
    return (sum);
}

void ft_printf_hex(unsigned char byte) {

	char *hex_digits = "0123456789abcdef";
	char first_digit = hex_digits[(byte >> 4) & 0x0F];
	char second_digit = hex_digits[byte & 0x0F];
	write(1, &first_digit, 1);
	write(1, &second_digit, 1);
}

unsigned char   *read_fd(int fd, size_t *out_len) {
    unsigned char   *buf = NULL;
    unsigned char   tmp[4096];
    size_t          total = 0;
    ssize_t         n;

    while ((n = read(fd, tmp, 4096)) > 0) {
        unsigned char *new = ft_realloc(buf, total, total + (size_t)n + 1);
        if (!new) {
            free(buf);
            *out_len = 0;
            return NULL;
        }
        buf = new;
        ft_memcpy(buf + total, tmp, (size_t)n);
        total += (size_t)n;
    }

    if (!buf) {
        buf = malloc(1);
        if (!buf)
        {
            *out_len = 0;
            return NULL;
        }
    }

    buf[total] = '\0';
    *out_len = total;
    return buf;
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0) {
		free(ptr); return (NULL);
	}
	if (!ptr) {return (malloc(new_size));}
	if (new_size == old_size) {return (ptr);}
	new_ptr = malloc(new_size);
	if (!new_ptr) {
		free(ptr); return (NULL);
	}
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}