/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:25:11 by mboulara          #+#    #+#             */
/*   Updated: 2019/10/21 22:05:19 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		parse_hash_flags(int argc, const char *argv[], t_cx data, t_cyph_f f)
{
	int				i;
	int				j;
	int				ret;

	data.flag = 0;
	ft_strupper(data.func_name);
	ret = 0;
	j = -1;
	argc += 1;
	while (--argc >= 1 && argv[++j] && argv[j][0] == '-')
	{
		i = 0;
		while (argv[j][++i])
			if (argv[j][i] == 'r' || argv[j][i] == 'q')
				data.flag |= (argv[j][i] == 'r') ? r_FLAG : q_FLAG;
			else if (argv[j][i] == 'p')
				ret += read_stdin(&data, f);
			else if (argv[j][i] == 's')
				ret += str_handler(&argc, &argv[j], &data, f);
			else
				return (print_usage_commands(data));
	}
	ret += (argc >= 1) ? read_file(&argv[j], &data, f) : read_stdin(&data, f);
	return (ret != 0);
}
