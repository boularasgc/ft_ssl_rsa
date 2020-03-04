/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl_encrypt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:47:25 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/23 16:16:57 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"
#include "ft_ssl.h"

size_t				rsautl_encrypt(uint8_t *buff, size_t size, size_t e,
size_t n)
{
	uint64_t		msg;
	size_t			i;
	size_t			byte;

	if (size > 8)
	{
		ft_printf("key is too big");
		return (0);
	}
	i = 0;
	msg = 0;
	while (i < size)
	{
		msg <<= 8;
		msg += buff[i++];
	}
	byte = mod_power(msg, e, n);
	return (byte);
}

size_t				rsautl_decrypt(uint8_t *buff, size_t size, size_t d,
size_t n)
{
	uint64_t		msg;
	size_t			i;
	size_t			byte;

	if (size > 8)
	{
		ft_printf("key is too big");
		return (0);
	}
	i = 0;
	msg = 0;
	while (i < size)
	{
		msg <<= 8;
		msg += buff[i++];
	}
	byte = mod_power(msg, d, n);
	return (byte);
}

void				print_rsautl(int fd, uint64_t encrypted, uint8_t flag)
{
	if ((flag & dec_F) && !(flag & hxdmp_F))
		print_rev_buffer(fd, &encrypted, sizeof(encrypted));
	else if ((flag & dec_F) && (flag & hxdmp_F))
		ft_hexdump(fd, &encrypted, sizeof(encrypted));
	else if ((flag & enc_F) && !(flag & hxdmp_F))
		print_rev_buffer(fd, &encrypted, sizeof(encrypted));
	else if ((flag & enc_F) && (flag & hxdmp_F))
		ft_hexdump(fd, &encrypted, sizeof(encrypted));
}

void				print_rev_buffer(int fd, void *p, size_t size)
{
	unsigned char	*x;
	int				z;

	z = size;
	x = p;
	while (--z >= 0)
		write(fd, &x[z], 1);
}
