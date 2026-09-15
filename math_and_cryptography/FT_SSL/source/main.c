/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalamit <csalamit@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:33:04 by csalamit          #+#    #+#             */
/*   Updated: 2026/09/15 18:16:07 by csalamit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"


static int launch_md5(t_flags flag, char *str, int fd, unsigned char *buf, size_t buf_len)
{
    unsigned char digest[16];
    unsigned char *content;
    size_t len;

    if (buf) {
        ft_md5_algo(buf, buf_len, digest);
        print_flag(flag, "MD5", digest, 16, str, -1);
        return (0);
    }
    if (fd >= 0) {
        content = read_fd(fd, &len);
        if (!content) {
            ft_error("ft_ssl: md5: ");
            ft_error(str ? str : "(stdin)");
            ft_error(": read error\n");
            return (1);
        }
        ft_md5_algo(content, len, digest);
        print_flag(flag, "MD5", digest, 16, str, 1);
        free(content);
        return (0);
    }
    ft_md5_algo((unsigned char *)str, ft_strlen(str), digest);
    print_flag(flag, "MD5", digest, 16, str, 0);
    return (0);
}

static int launch_sha256(t_flags flag, char *str, int fd, unsigned char *buf, size_t buf_len)
{
    unsigned char digest[32];
    unsigned char *content;
    size_t len;

    if (buf) {
        ft_sha256_algo(buf, buf_len, digest);
        print_flag(flag, "SHA256", digest, 32, str, -1);
        return (0);
    }
    if (fd >= 0) {
        content = read_fd(fd, &len);
        if (!content) {
            ft_error("ft_ssl: sha256: ");
            ft_error(str ? str : "(stdin)");
            ft_error(": read error\n");
            return (1);
        }
        ft_sha256_algo(content, len, digest);
        print_flag(flag, "SHA256", digest, 32, str, 1);
        free(content);
        return (0);
    }
    ft_sha256_algo((unsigned char *)str, ft_strlen(str), digest);
    print_flag(flag, "SHA256", digest, 32, str, 0);
    return (0);
}

static void usage(void)
{
    ft_error("usage: ft_ssl command [flags] [file/string]\n");
}

static void bad_command(char *cmd)
{
    ft_error("ft_ssl: Error: '");
    ft_error(cmd);
    ft_error("' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n");
}

static int open_file(char *algo, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        ft_error("ft_ssl: ");
        ft_error(algo);
        ft_error(": ");
        ft_error(filename);
        ft_error(": No such file or directory\n");
        return (-1);
    }
    return (fd);
}

static int parse_flags(int argc, char **argv, t_flags *f, int *first_file)
{
    int i = 2;
    int j;

    while (i < argc && argv[i][0] == '-' && argv[i][1]) {
        j = 1;
        while (argv[i][j]) {
            if (argv[i][j] == 'p')      f->p = 1;
            else if (argv[i][j] == 'q') f->q = 1;
            else if (argv[i][j] == 'r') f->r = 1;
            else if (argv[i][j] == 's') {
                f->s = 1;
                if (argv[i][j + 1]) {
                    ft_error("ft_ssl: -s must be the last flag of a group\n");
                    return (1);
                }
                if (i + 1 >= argc) {
                    ft_error("ft_ssl: option requires an argument -- s\n");
                    return (1);
                }
                i++;
                break;
            } else {
                ft_error("ft_ssl: illegal option -- ");
                write(2, &argv[i][j], 1);
                write(2, "\n", 1);
                usage();
                return (1);
            }
            j++;
        }
        i++;
    }
    *first_file = i;
    return (0);
}

int main(int argc, char **argv)
{
    char *commands[] = {"md5", "sha256", NULL};
    int (*hash[])(t_flags, char *, int, unsigned char *, size_t) = {launch_md5, launch_sha256};
    t_flags flags = {0};
    int cmd_idx = -1;
    int first_file = 2;
    int ret = 0;
    int i;
    int j;

    if (argc < 2) { usage(); return (1); }
    i = 0;
    while (commands[i]) {
        if (ft_strcmp(argv[1], commands[i]) == 0) { cmd_idx = i; break; }
        i++;
    }
    if (cmd_idx == -1) { bad_command(argv[1]); return (1); }
    if (parse_flags(argc, argv, &flags, &first_file))
        return (1);

    /* -p : stdin en premier */
    if (flags.p) {
        size_t len;
        unsigned char *content = read_fd(0, &len);
        if (!content) {
            ft_error("ft_ssl: read error on stdin\n");
            ret = 1;
        } else {
            hash[cmd_idx](flags, (char *)content, -1, content, len);
            free(content);
        }
    }

    i = 2;
    while (i < first_file) {
        if (argv[i][0] == '-' && argv[i][1]) {
            j = 1;
            while (argv[i][j]) {
                if (argv[i][j] == 's') {
                    hash[cmd_idx](flags, argv[i + 1], -1, NULL, 0);
                    i++;
                    break;
                }
                j++;
            }
        }
        i++;
    }
	
	//for files
    if (first_file < argc) {
        i = first_file;
        while (i < argc) {
            int fd = open_file(commands[cmd_idx], argv[i]);
            if (fd < 0)
                ret = 1;
            else {
                if (hash[cmd_idx](flags, argv[i], fd, NULL, 0))
                    ret = 1;
                close(fd);
            }
            i++;
        }
    } else if (!flags.p && !flags.s)
        hash[cmd_idx](flags, NULL, 0, NULL, 0);

    return (ret);
}