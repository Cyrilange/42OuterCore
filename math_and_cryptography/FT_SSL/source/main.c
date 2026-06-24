/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalamit <csalamit@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:33:04 by csalamit          #+#    #+#             */
/*   Updated: 2026/06/05 12:25:05 by csalamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

static void	launch_md5(t_flags flag, char *str, int fd, unsigned char *buf, size_t buf_len) {
	unsigned char	digest[16];
	unsigned char	*content;
	size_t			len;

	if (buf) {
		ft_md5_algo(buf, buf_len, digest);
		print_flag(flag, "MD5", digest, 16, str, -1);
		return ;
	}
	if (fd >= 0) {
		content = read_fd(fd, &len);
		ft_md5_algo(content ? content : (unsigned char *)"", len, digest);
		print_flag(flag, "MD5", digest, 16, str, 1);
		if (content)
			free(content);
	} else {
		ft_md5_algo((unsigned char *)str, ft_strlen(str), digest);
		print_flag(flag, "MD5", digest, 16, str, 0);
	}
}

static void	launch_sha256(t_flags flag, char *str, int fd, unsigned char *buf, size_t buf_len) {
	unsigned char	digest[32];
	unsigned char	*content;
	size_t			len;

	if (buf) {
		ft_sha256_algo(buf, buf_len, digest);
		print_flag(flag, "SHA256", digest, 32, str, -1);
		return ;
	}
	if (fd >= 0) {
		content = read_fd(fd, &len);
		ft_sha256_algo(content ? content : (unsigned char *)"", len, digest);
		print_flag(flag, "SHA256", digest, 32, str, 1);
		if (content)
			free(content);
	} else {
		ft_sha256_algo((unsigned char *)str, ft_strlen(str), digest);
		print_flag(flag, "SHA256", digest, 32, str, 0);
	}
}

static int	open_file(char *algo, char *filename) {
	int	fd;

	if (!filename) {
		ft_error("No file provided\n");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		ft_error("ft_ssl: ");
		ft_error(algo);
		ft_error(" : ");
		ft_error(filename);
		ft_error(": No such file or directory\n");
		return (-1);
	}
	return (fd);
}

static void	close_file(int fd) {
	if (fd >= 0)
		close(fd);
}

int	main(int argc, char **argv) {
	char	*commands[] = {"md5", "sha256", NULL};
	void	(*hash_functions[])(t_flags, char *, int, unsigned char *, size_t) = {launch_md5, launch_sha256};
	t_flags	flags = {0};
	int		cmd_idx = -1;
	int		arg_idx = 2;

	if (argc < 2) {
		ft_error("usage: ft_ssl command [flags] [file/string]\n");
		return (1);
	}
	for (int i = 0; commands[i]; i++) {
		if (ft_strcmp(argv[1], commands[i]) == 0) {
			cmd_idx = i;
			break ;
		}
	}
	if (cmd_idx == -1) {
		ft_error("ft_ssl: Error: '");
		ft_error(argv[1]);
		ft_error("' is an invalid command.\n");
		return (1);
	}
	while (arg_idx < argc && argv[arg_idx][0] == '-') {
		int j = 1;
		while (argv[arg_idx][j]) {
			if (argv[arg_idx][j] == 'p') flags.p = 1;
			else if (argv[arg_idx][j] == 'q') flags.q = 1;
			else if (argv[arg_idx][j] == 'r') flags.r = 1;
			else if (argv[arg_idx][j] == 's') {
				flags.s = 1;
				j++;
				break ;
			} else {
				ft_error("unknown option\n");
				return (1);
			}
			j++;
		}
		arg_idx++;
	}
	if (flags.p) {
		unsigned char	*content;
		size_t			len;
		char			saved;

		content = read_fd(0, &len);
		if (content) {
			size_t	hash_len = len;
			saved = 0;
			if (len > 0 && content[len - 1] == '\n') {
				saved = content[len - 1];
				content[len - 1] = '\0';
				len--;
			}
			if (saved)
				content[len] = saved;
			hash_functions[cmd_idx](flags, (char *)content, -1, content, hash_len);
			free(content);
		}
	}
	if (flags.s) {
		if (arg_idx >= argc) {
			ft_error("ft_ssl: option requires an argument -- s\n");
			return (1);
		}
		hash_functions[cmd_idx](flags, argv[arg_idx], -1, NULL, 0);
		arg_idx++;
	}
	if (arg_idx < argc) {
		while (arg_idx < argc) {
			int fd = open_file(commands[cmd_idx], argv[arg_idx]);
			if (fd >= 0) {
				hash_functions[cmd_idx](flags, argv[arg_idx], fd, NULL, 0);
				close_file(fd);
			}
			arg_idx++;
		}
	} else if (!flags.s && !flags.p)
		hash_functions[cmd_idx](flags, NULL, 0, NULL, 0);
	return (0);
}