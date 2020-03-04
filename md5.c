/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:08:04 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 08:21:53 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_md5.h"
#include <fcntl.h>

static const int		g_k_table[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static const int		g_s_table[64] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

void			construct_mssg(t_cx data, t_ctx *h)
{
	uint64_t	bit_len;

	h->ini_len = ft_strlen(data.line);
	h->newlen = ((((h->ini_len + 8) / 64) + 1) * 64) - 8;
	h->msg = (uint8_t *)malloc(h->newlen + sizeof(uint64_t));
	ft_bzero(h->msg, h->newlen + sizeof(uint64_t));
	ft_memcpy(h->msg, data.line, h->ini_len);
	h->msg[h->ini_len] = 128;
	bit_len = (h->ini_len * CHAR_BIT) % UINT64_MAX;
	ft_memcpy(h->msg + h->newlen, &bit_len, sizeof(bit_len));
}

void			copy_variables(t_ctx *h, u_int32_t j)
{
	h->f = (h->f + h->a + g_k_table[j] + h->w[h->g]) % UINT32_MAX;
	h->temp = h->d;
	h->d = h->c;
	h->c = h->b;
	h->b = (h->b + rotate_left(h->f, g_s_table[j])) % UINT32_MAX;
	h->a = h->temp;
}

void			md5_main_loop(t_ctx *h, u_int32_t j)
{
	if (j < 16)
	{
		h->f = (h->b & h->c) | ((~h->b) & h->d);
		h->g = j;
	}
	else if (j < 32)
	{
		h->f = (h->d & h->b) | ((~h->d) & h->c);
		h->g = (5 * j + 1) % 16;
	}
	else if (j < 48)
	{
		h->f = h->b ^ h->c ^ h->d;
		h->g = (3 * j + 5) % 16;
	}
	else
	{
		h->f = h->c ^ (h->b | (~h->d));
		h->g = (7 * j) % 16;
	}
	copy_variables(h, j);
}

void			intialilze_md5_ctx(t_ctx *h, t_cx data)
{
	construct_mssg(data, h);
	h->state[0] = 0x67452301;
	h->state[1] = 0xefcdab89;
	h->state[2] = 0x98badcfe;
	h->state[3] = 0x10325476;
}

int				message_digest_md5(t_cx data)
{
	t_ctx		h;
	uint32_t	i;
	uint32_t	j;

	i = 0;
	intialilze_md5_ctx(&h, data);
	while (i < h.newlen)
	{
		j = -1;
		h.w = (uint32_t *)(h.msg + i);
		h.a = h.state[0];
		h.b = h.state[1];
		h.c = h.state[2];
		h.d = h.state[3];
		while (++j < 64)
			md5_main_loop(&h, j);
		h.state[0] = (h.state[0] + h.a) % UINT32_MAX;
		h.state[1] = (h.state[1] + h.b) % UINT32_MAX;
		h.state[2] = (h.state[2] + h.c) % UINT32_MAX;
		h.state[3] = (h.state[3] + h.d) % UINT32_MAX;
		j = -1;
		i += 64;
	}
	print_md5_message(h, data);
	return (0);
}
