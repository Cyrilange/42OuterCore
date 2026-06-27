/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalamit <csalamit@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 10:08:07 by csalamit          #+#    #+#             */
/*   Updated: 2026/06/27 19:23:47 by csalamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

static void	print_digest(unsigned char *d, int len) {
	int	i = 0;
	while (i < len) {
		ft_printf_hex(d[i]);
		i++;
	}
}

void	print_flag(t_flags f, char *algo, unsigned char *d, int len, char *str, int is_file) {
	if (is_file == -1) {
		size_t	slen = str ? ft_strlen(str) : 0;
		if (slen > 0 && str[slen - 1] == '\n') slen--;
		if (!f.q) {
			if (str) write(1, str, slen);
			write(1, " ", 1);
		}
		print_digest(d, len);
		write(1, "\n", 1);
		return ;
	}
	if (f.q) {
		print_digest(d, len);
		write(1, "\n", 1);
		return ;
	}
	if (f.r) {
		print_digest(d, len);
		write(1, "  ", 2);
		if (str) {
			if (is_file == 1)
				write(1, str, ft_strlen(str));
			else {
				write(1, "\"", 1);
				write(1, str, ft_strlen(str));
				write(1, "\"", 1);
			}
		}
		write(1, "\n", 1);
		return ;
	}
	if (is_file == 1) {
		if (!str) {
			write(1, algo, ft_strlen(algo));
			write(1, " (stdin)= ", 11);
		} else {
			write(1, algo, ft_strlen(algo));
			write(1, " (", 2);
			write(1, str, ft_strlen(str));
			write(1, ") = ", 4);
		}
	} else if (is_file == 0) {
		write(1, algo, ft_strlen(algo));
		write(1, " (\"", 3);
		if (str)
			write(1, str, ft_strlen(str));
		write(1, "\")= ", 4);
	}
	print_digest(d, len);
	write(1, "\n", 1);
}