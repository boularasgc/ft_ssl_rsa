/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_64_encode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:44:10 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/21 21:24:58 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"
#include "ft_base64.h"

#define C_SET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

void			main_loop(t_b64_d *b, uint8_t *buf, size_t size)
{
	while ((size_t)b->i < ((size / 3) * 3))
	{
		b->msg[b->j] = C_SET[buf[b->i] >> 2];
		b->msg[b->j + 1] = C_SET[((buf[b->i] & 0x3) << 4) |
		((buf[b->i + 1] & 0xF0) >> 4)];
		b->msg[b->j + 2] = C_SET[((buf[b->i + 1] & 0x0F) << 2) |
		((buf[b->i + 2] & 0xC0) >> 6)];
		b->msg[b->j + 3] = C_SET[buf[b->i + 2] & 0x3F];
		b->i += 3;
		b->j += 4;
	}
}

char			*base64_encode(uint8_t *buf, size_t size)
{
	t_b64_d	b;

	b.msg = (unsigned char *)ft_memalloc(((size + 2) / 3) * 4);
	b.i = 0;
	b.j = 0;
	b.byte = 0;
	main_loop(&b, buf, size);
	if ((size_t)b.i + 1 == size)
	{
		b.msg[b.j] = C_SET[buf[b.i] >> 2];
		b.msg[b.j + 1] = C_SET[((buf[b.i] & 0x3) << 4) |
		((b.byte & 0xF0) >> 4)];
		b.msg[b.j + 2] = '=';
		b.msg[b.j + 3] = '=';
	}
	else if ((size_t)b.i + 2 == size)
	{
		b.msg[b.j] = C_SET[buf[b.i] >> 2];
		b.msg[b.j + 1] = C_SET[((buf[b.i] & 0x3) << 4) |
		((buf[b.i + 1] & 0xF0) >> 4)];
		b.msg[b.j + 2] = C_SET[((buf[b.i + 1] & 0x0F) << 2) |
		((b.byte & 0xC0) >> 6)];
		b.msg[b.j + 3] = '=';
	}
	return ((char *)b.msg);
}

void			print_base64_msg(int fd, char *msg, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		if (i == 64)
			write(fd, "\n", 1);
		write(fd, &msg[i++], 1);
	}
	write(fd, "\n", 1);
}
