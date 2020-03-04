/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:44:05 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/06 19:31:11 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"

void		copy_indianese(void *src, void *dest, size_t srcsz, size_t destsz)
{
	uint8_t *a;
	uint8_t *b;
	size_t	i;

	a = (uint8_t *)src;
	i = 0;
	b = (uint8_t *)dest;
	destsz -= 1;
	while (i < srcsz)
	{
		b[destsz] = a[i];
		i++;
		destsz--;
	}
}

size_t		ft_size_bytes_occupy(void *p, size_t size)
{
	uint8_t *a;
	int		i;
	int		sz;

	a = (uint8_t *)p;
	i = 0;
	sz = size;
	while ((int)a[--sz] == 0)
		i++;
	if (a[sz] >> 7 == 1)
		size++;
	return (size - i);
}

uint8_t		*construct_int_msg(void *p, size_t size)
{
	uint8_t	*msg;
	size_t	intsz;
	size_t	len;

	intsz = ft_size_bytes_occupy(&(*p), size);
	msg = ft_memalloc(2 + intsz);
	msg[0] = 0x2;
	msg[1] = intsz;
	len = intsz > size ? size : intsz;
	if (len > 1)
		copy_indianese(&(*p), &msg[0], len, intsz + 2);
	return (msg);
}

size_t		get_integer_length(void *p, size_t sz)
{
	uint8_t	*bytes;
	uint8_t	onebyte;

	bytes = (uint8_t *)p;
	onebyte = bytes[sz - 1];
	if ((onebyte >> (8 - 1)) & 1)
		sz += 1;
	return (sz);
}

size_t		get_bit_length(void *p, size_t sz)
{
	uint8_t	*bytes;
	uint8_t	onebyte;
	int		i;

	i = 0;
	bytes = (uint8_t *)p;
	onebyte = bytes[sz - 1];
	while (!onebyte)
		onebyte = bytes[(--sz) - 1];
	while (onebyte)
	{
		onebyte >>= 1;
		i++;
	}
	return ((sz - 1) * 8 + i);
}
