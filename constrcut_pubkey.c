/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constrcut_pubkey.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 19:36:37 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 08:27:24 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"

uint8_t			*constrcut_pubkey(t_rsa64bit rsa)
{
	t_pbk_str	b;

	b.pubexpo = construct_int_msg(&rsa.pubexpo, sizeof(rsa.pubexpo));
	b.modulus = construct_int_msg(&rsa.modulus, sizeof(rsa.modulus));
	b.sequence3 = ft_memalloc(2);
	b.sequence3[0] = 0x30;
	b.sequence3[1] = b.modulus[1] + b.pubexpo[1] + 4;
	b.bit_str = ft_memalloc(3);
	b.bit_str[0] = 0x03;
	b.bit_str[1] = b.sequence3[1] + 3;
	b.null_id = ft_memalloc(2);
	b.null_id[0] = 0x05;
	b.obj_id = ft_memalloc(11);
	ft_memcpy(b.obj_id + 2, object_id_func(), 9);
	b.obj_id[1] = 0x9;
	b.obj_id[0] = 0x6;
	b.sequence2 = ft_memalloc(2);
	b.sequence2[0] = 0x30;
	b.sequence2[1] = b.obj_id[1] + 4;
	b.sequence = ft_memalloc(2);
	b.sequence[0] = 0x30;
	b.sequence[1] = b.bit_str[1] + 2 + b.sequence2[1] + 2;
	return (concatinate_pbk_msg(&b, b.sequence[1] + 2));
}

uint8_t			*concatinate_pbk_msg(t_pbk_str *b, size_t size)
{
	uint8_t		*msg;

	msg = ft_memalloc(size);
	ft_memcpy(msg, b->sequence, 2);
	ft_memcpy(msg + 2, b->sequence2, 2);
	ft_memcpy(msg + 4, b->obj_id, 11);
	ft_memcpy(msg + 15, b->null_id, 2);
	ft_memcpy(msg + 17, b->bit_str, 3);
	ft_memcpy(msg + 17, b->bit_str, 3);
	ft_memcpy(msg + 20, b->sequence3, 2);
	ft_memcpy(msg + 22, b->modulus, b->modulus[1] + 2);
	ft_memcpy(msg + 22 + b->modulus[1] + 2, b->pubexpo, b->pubexpo[1] + 2);
	return (msg);
}

uint8_t			*object_id_func(void)
{
	uint8_t		*obj;

	obj = ft_memalloc(9);
	obj[0] = 0x2A;
	obj[1] = 0x86;
	obj[2] = 0x48;
	obj[3] = 0x86;
	obj[4] = 0xF7;
	obj[5] = 0x0D;
	obj[6] = 0x01;
	obj[7] = 0x01;
	obj[8] = 0x01;
	return (obj);
}

void			print_pubkey_rsa_message(t_rsa64bit *rsa, size_t size)
{
	write(rsa->outfile, "-----BEGIN PUBLIC KEY-----\n", 27);
	print_base64_msg(rsa->outfile, rsa->msg, size);
	write(rsa->outfile, "-----END PUBLIC KEY-----\n", 26);
}
