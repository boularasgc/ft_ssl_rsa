/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 00:30:01 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/23 15:06:12 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_rsa.h"

t_rsa_cmds	g_rsa_dis[] =
{
	{"-text", t_F},
	{"-check", c_F},
	{"-noout", n_F},
	{"-modulus", m_F},
	{"-pubin", pbin_F},
	{"-pubout", pbout_F},
	{"-in", in_F},
	{"-out", out_F},
	{NULL, 0},
};

int				rsa_parser(int argc, const char *argv[], t_cx data, t_cyph_f f)
{
	t_rsa64bit	rsa;

	parse_rsa_commands(argc, argv, &rsa);
	(void)data;
	(void)f;
	free_rsa_struct(&rsa);
	return (0);
}

int				parse_rsa_commands(int c, char const *argv[], t_rsa64bit *rsa)
{
	int			i;
	uint8_t		flag;

	i = 0;
	flag = 0;
	rsa->outfile = STDOUT;
	rsa->rfile = STDIN;
	if (c == 0)
	{
		print_rsa_info(*rsa, flag);
		return (0);
	}
	while (i < c && argv[i][0] == '-')
		rsa_commands_cases(argv, &flag, &i, rsa);
	if (i == c)
		print_rsa_info(*rsa, flag);
	else
	{
		ft_printf(KCYN"RSA COMMAND: [-in file] [-out file] [-text] [-noout]");
		ft_printf(" [-modulus] [-check] [-pubin] [-pubout]"RESET);
	}
	return (0);
}

void			rsa_commands_cases(const char *argv[], uint8_t *flag, int *i,
t_rsa64bit *rsa)
{
	int			j;

	j = -1;
	while (g_rsa_dis[++j].cmd_name != NULL)
		if (!ft_strcmp(g_rsa_dis[j].cmd_name, argv[*i]))
		{
			*flag |= g_rsa_dis[j].flag;
			break ;
		}
	if (!ft_strcmp(argv[*i], "-out"))
		rsa->filename2 = ft_strdup(argv[++(*i)]);
	if (!ft_strcmp(argv[*i], "-in"))
		rsa->filename1 = ft_strdup(argv[++(*i)]);
	if (g_rsa_dis[j].cmd_name == NULL)
		*i += 20;
	*i += 1;
}

char			*rsa_checker(t_rsa64bit rsa)
{
	t_rsa64bit	b;
	uint64_t	f_n;

	if (ft_ssl_is_prime(rsa.prime1) && ft_ssl_is_prime(rsa.prime2) &&
	ft_ssl_is_prime(rsa.pubexpo))
	{
		b.prime1 = rsa.prime1;
		b.prime2 = rsa.prime2;
		b.modulus = (uint64_t)b.prime1 * (uint64_t)b.prime2;
		f_n = ((uint64_t)(b.prime1 - 1) * (uint64_t)(b.prime2 - 1));
		b.priexpo = mul_inv(rsa.pubexpo, f_n);
		b.expo1 = b.priexpo % (b.prime1 - 1);
		b.expo2 = b.priexpo % (b.prime2 - 1);
		b.coef = mul_inv(b.prime2, b.prime1);
		if (b.modulus == rsa.modulus && b.priexpo == rsa.priexpo &&
		b.coef == rsa.coef)
			return ("RSA key ok\n");
	}
	return ("RSA key error:Check values pqne\n");
}
