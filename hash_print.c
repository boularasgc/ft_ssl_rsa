/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 21:33:57 by mboulara          #+#    #+#             */
/*   Updated: 2019/11/06 23:24:02 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"
#include "ft_sha256.h"
#include "ft_ssl.h"

void			print_hashed_message(t_ctx h)
{
	uint8_t		*p;
	int			i;

	i = -1;
	while (++i < 4)
	{
		p = (uint8_t *)&h.state[i];
		ft_printf(KGRN"%2.2x%2.2x%2.2x%2.2x"RESET,
			p[0], p[1], p[2], p[3], &h.state[i]);
	}
}

void			print_hashed_string(t_ctx h, t_cx data)
{
	if (!(r_FLAG & data.flag) && !(q_FLAG & data.flag))
	{
		ft_printf("%s (%c", data.func_name, 34);
		ft_printf(KYEL"%s"RESET, data.line);
		ft_printf("%c) = ", 34);
		print_hashed_message(h);
		ft_printf("\n");
	}
	else if (q_FLAG & data.flag)
	{
		print_hashed_message(h);
		ft_printf("\n");
	}
	else if (r_FLAG & data.flag)
	{
		print_hashed_message(h);
		ft_printf(" %c", 34);
		ft_printf(KYEL"%s"RESET, data.line);
		ft_printf("%c", 34);
		ft_printf("\n");
	}
}

void			print_hashed_file(t_ctx h, t_cx data)
{
	if (!(r_FLAG & data.flag) && !(q_FLAG & data.flag))
	{
		ft_printf("%s (", data.func_name);
		ft_printf(KCYN"%s"RESET, data.file);
		ft_printf(") = ");
		print_hashed_message(h);
		ft_printf("\n");
	}
	else if (q_FLAG & data.flag)
	{
		print_hashed_message(h);
		ft_printf("\n");
	}
	else if ((r_FLAG & data.flag))
	{
		print_hashed_message(h);
		ft_printf(KYEL" %s"RESET, data.file);
		ft_printf("\n");
	}
}

void			print_md5_message(t_ctx h, t_cx data)
{
	if (f_FLAG & data.flag)
		print_hashed_file(h, data);
	else if (s_FLAG & data.flag)
		print_hashed_string(h, data);
	else
	{
		ft_printf("%s");
		print_hashed_message(h);
		ft_printf("\n");
	}
}

int				print_usage_commands(t_cx data)
{
	printf(KRED"Usage: %s [-pqr] [-s string] [files ...]"RESET,
	data.func_name);
	return (1);
}
