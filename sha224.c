/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:56:14 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 08:00:05 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_sha224.h"

static const int	g_k[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void			intialilze_224_ctx(t_224ctx *h, t_cx data)
{
	construct_sha224_mssg(data, h);
	h->state[0] = 0xc1059ed8;
	h->state[1] = 0x367cd507;
	h->state[2] = 0x3070dd17;
	h->state[3] = 0xf70e5939;
	h->state[4] = 0xffc00b31;
	h->state[5] = 0x68581511;
	h->state[6] = 0x64f98fa7;
	h->state[7] = 0xbefa4fa4;
}

void			copy_mesg_224_w(t_224ctx *h, size_t l)
{
	uint32_t i;
	uint32_t j;

	i = 0;
	j = 0;
	ft_bzero(h->w, 64);
	while (i < 16)
	{
		h->w[i] = (h->msg[j + l] << 24) | (h->msg[j + l + 1] << 16);
		h->w[i] |= (h->msg[j + l + 2] << 8) | (h->msg[j + l + 3]);
		++i;
		j += 4;
	}
	while (i < 64)
	{
		h->w[i] = wj1_(h->w[i - 2]) + h->w[i - 7];
		h->w[i] += wj0_(h->w[i - 15]) + h->w[i - 16];
		i++;
	}
}

void			init_wv_224hash(t_224ctx *h)
{
	h->a = h->state[0];
	h->b = h->state[1];
	h->c = h->state[2];
	h->d = h->state[3];
	h->e = h->state[4];
	h->f = h->state[5];
	h->g = h->state[6];
	h->h = h->state[7];
}

void			compression_224loop(t_224ctx *h)
{
	uint32_t	t1;
	uint32_t	t2;
	int			i;

	i = 0;
	while (i < 64)
	{
		t1 = h->h + ep1_(h->e) + ch_(h->e, h->f, h->g) + g_k[i] + h->w[i];
		t2 = ep0_(h->a) + maj_(h->a, h->b, h->c);
		h->h = h->g;
		h->g = h->f;
		h->f = h->e;
		h->e = h->d + t1;
		h->d = h->c;
		h->c = h->b;
		h->b = h->a;
		h->a = t1 + t2;
		i++;
	}
}

int				message_digest_sh224(t_cx data)
{
	t_224ctx	h;
	size_t		i;
	uint32_t	j;

	j = -1;
	i = 0;
	intialilze_224_ctx(&h, data);
	while (i < h.newlen)
	{
		copy_mesg_224_w(&h, i);
		init_wv_224hash(&h);
		compression_224loop(&h);
		h.state[0] += h.a;
		h.state[1] += h.b;
		h.state[2] += h.c;
		h.state[3] += h.d;
		h.state[4] += h.e;
		h.state[5] += h.f;
		h.state[6] += h.g;
		h.state[7] += h.h;
		i += 64;
	}
	print_224_message(h, data);
	return (0);
}
