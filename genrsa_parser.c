/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 23:40:04 by mboulara          #+#    #+#             */
/*   Updated: 2019/12/19 16:33:49 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_rsa.h"

int		genrsa_parser(int argc, const char *argv[], t_cx data, t_cyph_f f)
{
	if (argc > 1)
	{
		ft_printf("%d", argc);
	}
	(void)data.file;
	(void)f;
	(void)argv[0];
	return (genrsa());
}
