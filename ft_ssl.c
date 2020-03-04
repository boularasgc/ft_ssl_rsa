/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:49:18 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/21 16:29:32 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <string.h>

t_command	g_dispatch[] =
{
	{"md5", 1, message_digest_md5, parse_hash_flags},
	{"sha256", 2, message_digest_sh256, parse_hash_flags},
	{"sha224", 3, message_digest_sh224, parse_hash_flags},
	{"prime", 4, NULL, prime_parser},
	{"genrsa", 5, NULL, genrsa_parser},
	{"rsa", 6, NULL, rsa_parser},
	{"rsautl", 6, NULL, rsautl_parser},
	{NULL, -1, NULL, NULL},
};

int			ft_ssl(int cnt, const char **argv)
{
	int		i;
	t_cx	data;

	if (cnt >= 1)
	{
		i = -1;
		while (g_dispatch[++i].cyp_name != NULL)
			if (!ft_strcmp(g_dispatch[i].cyp_name, argv[0]))
			{
				data.func_name = ft_strdup(argv[0]);
				return (g_dispatch[i].parse_func(--cnt, ++argv, data,
					g_dispatch[i].func));
			}
		if (g_dispatch[i].cyp_name == NULL)
			write(1, "commands are :\n md5 \n sha256", 28);
	}
	return (1);
}

int			main(int cnt, const char **argv)
{
	int		i;

	if (cnt >= 2)
		ft_ssl(--cnt, ++argv);
	else
	{
		i = -1;
		write(1, "comands: \n", 10);
		while (g_dispatch[++i].cyp_name != NULL)
			ft_printf(KRED"%s\n"RESET, g_dispatch[i].cyp_name);
		return (1);
	}
	return (0);
}
