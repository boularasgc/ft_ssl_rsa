/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 20:07:10 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/23 16:32:18 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"
#include "ft_ssl.h"

t_rsa_cmds	g_rsautl_dis[] =
{
	{"-in", t_F},
	{"-out", out_F},
	{"-inkey", in_F},
	{"-pubin", pbin_F},
	{"-encrypt", enc_F},
	{"-decrypt", dec_F},
	{"-hexdump", hxdmp_F},
	{NULL, 0},
};

int				rsautl_parser(int argc, const char *argv[], t_cx data,
t_cyph_f f)
{
	int			i;
	uint8_t		flag;
	t_rsa64bit	rsa;

	(void)data;
	(void)f;
	i = 0;
	flag = 0;
	flag = parse_rsautl_args(argc, argv, &rsa);
	rsautl_execute(flag, &rsa);
	free_rsa_struct(&rsa);
	return (0);
}

uint8_t			parse_rsautl_args(int c, const char *argv[], t_rsa64bit *rsa)
{
	int			i;
	uint8_t		flag;

	i = 0;
	flag = 0;
	while (i < c && argv[i][0] == '-')
		flag |= rsautl_cmnds_cases(argv, &i, rsa);
	if (i > c)
	{
		ft_printf(KCYN" [-in file] [-out file] [-inkey file] [-pubin]");
		ft_printf("  [-encrypt][-decrypt] [-hexdump]"RESET);
		exit(0);
	}
	else if (i == c)
		return (flag);
	return (0);
}

uint8_t			rsautl_cmnds_cases(const char *argv[], int *i, t_rsa64bit *rsa)
{
	int			j;
	uint8_t		flag;

	flag = 0;
	j = -1;
	while (g_rsautl_dis[++j].cmd_name != NULL)
		if (!ft_strcmp(g_rsautl_dis[j].cmd_name, argv[*i]))
		{
			flag |= g_rsautl_dis[j].flag;
			break ;
		}
	if (!ft_strcmp(argv[*i], "-out"))
		rsa->filename2 = ft_strdup(argv[++(*i)]);
	if (!ft_strcmp(argv[*i], "-in"))
		rsa->filename3 = ft_strdup(argv[++(*i)]);
	if (!ft_strcmp(argv[*i], "-inkey"))
		rsa->filename1 = ft_strdup(argv[++(*i)]);
	if (g_rsautl_dis[j].cmd_name == NULL)
		*i += 20;
	*i += 1;
	return (flag);
}

int				rsautl_execute(uint8_t flag, t_rsa64bit *rsa)
{
	char		*line;
	int			i;
	size_t		encrypted;

	if ((flag & dec_F) && (flag & pbin_F))
		return (0);
	if (!(flag & in_F))
		return (0);
	else
		rsa_file_select(rsa, flag);
	i = rsautl_readfile(flag, rsa, &line);
	if (i == 0)
		return (0);
	encrypted = (flag & enc_F) ? rsautl_encrypt((uint8_t *)line,
	ft_strlen(line), rsa->pubexpo, rsa->modulus) : 0;
	encrypted = (flag & dec_F) ? rsautl_decrypt((uint8_t *)line,
	ft_strlen(line), rsa->priexpo, rsa->modulus) : encrypted;
	rsa->outfile = (flag & out_F) ? open_rsaoutput_file(rsa) : STDOUT;
	print_rsautl(rsa->outfile, encrypted, flag);
	return (1);
}

int				rsautl_readfile(uint8_t flag, t_rsa64bit *rsa, char **line)
{
	int			fd;
	int			i;

	fd = (flag & t_F) ? open(rsa->filename3, O_RDONLY) : STDIN;
	i = stringyfy_file_desc(fd, line);
	if (ft_strlen(*line) > 8)
		return (0);
	if (fd > STDERR)
		close(fd);
	if (i)
		return (1);
	else
		return (0);
}
