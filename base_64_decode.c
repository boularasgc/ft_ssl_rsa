/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_64_decode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:36:43 by mboulara          #+#    #+#             */
/*   Updated: 2019/12/30 19:39:01 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"
#include "libft/libft.h"
#include "ft_base64.h"

#define C_ST "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="

static const int	g_de_lkuptbl[] = {
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 62, 80, 80, 80, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 80, 80, 80, 64, 80, 80,
	80, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 80, 80, 80, 80, 80,
	80, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 80, 80, 80, 80, 80
};

static void		b64_mainloop_block(t_b64_d *b, char *str)
{
	b->bytes[0] = g_de_lkuptbl[(int)str[b->i]];
	b->bytes[1] = g_de_lkuptbl[(int)str[b->i + 1]];
	b->bytes[2] = g_de_lkuptbl[(int)str[b->i + 2]];
	b->bytes[3] = g_de_lkuptbl[(int)str[b->i + 3]];
	b->msg[b->j] = (b->bytes[0] << 2 | ((b->bytes[1] & 0xF0) >> 4));
	b->msg[b->j + 1] = (((b->bytes[1] & 0x0F) << 4) |
	((b->bytes[2] & 0x3C) >> 2));
	b->msg[b->j + 2] = (((b->bytes[2] & 0x03) << 6) | (b->bytes[3] & 0x3F));
	b->i += 4;
	b->j += 3;
}

uint8_t			*base_64_decoder(char *str, size_t len)
{
	t_b64_d		b;

	b.lastfour = (str[len - 1] == '=') ? ((len / 4) - 1) * 4 : len;
	b.i = 0;
	b.j = 0;
	ft_bzero(&b.bytes, sizeof(b.bytes));
	b.msg = ft_memalloc((len / 4) * 3);
	while (b.i < b.lastfour)
	{
		b64_mainloop_block(&b, &(*str));
	}
	if (b.lastfour < len)
	{
		b.bytes[0] = g_de_lkuptbl[(int)str[b.i]];
		b.bytes[1] = g_de_lkuptbl[(int)str[b.i + 1]];
		b.msg[b.j] = (b.bytes[0] << 2 | ((b.bytes[1] & 0xF0) >> 4));
		if (str[b.i + 2] != '=')
		{
			b.bytes[2] = g_de_lkuptbl[(int)str[b.i + 2]];
			b.msg[b.j + 1] = (((b.bytes[1] & 0x0F) << 4) |
			((b.bytes[2] & 0x3C) >> 2));
		}
	}
	return (b.msg);
}

int				check_base64_format(char *str, size_t len)
{
	int			i;
	uint8_t		bytes[2];
	uint8_t		msglen;

	i = 0;
	while ((size_t)i < len)
	{
		if (!ft_strchr(C_ST, str[i]))
			break ;
		i++;
	}
	bytes[0] = g_de_lkuptbl[(int)str[1]];
	bytes[1] = g_de_lkuptbl[(int)str[2]];
	msglen = (((bytes[0] & 0x0F) << 4) | ((bytes[1] & 0x3C) >> 2));
	return ((size_t)i == len && (len % 4 == 0) &&
			((((size_t)msglen + 4) / 3) * 4 == len));
}
