/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_ext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:26:28 by mboulara          #+#    #+#             */
/*   Updated: 2019/10/21 21:39:45 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_sha256.h"

void			print_256_message(t_256ctx h, t_cx data)
{
	uint8_t		*p;
	int			i;

	if (f_FLAG & data.flag)
		ft_printf("%s(%s)= ", data.func_name, data.file);
	else if (s_FLAG & data.flag)
		ft_printf("%s(%c%s%c)= ", data.func_name, 34, data.line, 34);
	i = -1;
	while (++i < 8)
	{
		p = (uint8_t *)&h.state[i];
		ft_printf(KMAG"%2.2x%2.2x%2.2x%2.2x"RESET,
			p[3], p[2], p[1], p[0], &h.state[i]);
	}
	ft_printf("\n");
}

void			construct_sha256_mssg(t_cx data, t_256ctx *h)
{
	uint64_t	bit_len;
	int			maxlen;

	h->ini_len = ft_strlen(data.line);
	h->newlen = ((((h->ini_len + 8) / 64) + 1) * 64) - 8;
	maxlen = h->newlen / 64 + 1;
	h->msg = (uint8_t *)malloc(h->newlen);
	ft_bzero(h->msg, h->newlen);
	ft_memcpy(h->msg, data.line, h->ini_len);
	h->msg[h->ini_len] = 128;
	bit_len = h->ini_len * 8;
	h->msg[h->newlen + 7] = bit_len;
	h->msg[h->newlen + 6] = bit_len >> 8;
	h->msg[h->newlen + 5] = bit_len >> 16;
	h->msg[h->newlen + 4] = bit_len >> 24;
	h->msg[h->newlen + 3] = bit_len >> 32;
	h->msg[h->newlen + 2] = bit_len >> 40;
	h->msg[h->newlen + 1] = bit_len >> 48;
	h->msg[h->newlen] = bit_len >> 56;
}
