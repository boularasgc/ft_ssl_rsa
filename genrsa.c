/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:09:37 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 08:28:32 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"
#define COEFF 65537

int				genrsa(void)
{
	t_rsa64bit	rsa;
	uint64_t	f_n;

	rsa.outfile = STDOUT;
	rsa.pubexpo = COEFF;
	get_appropriate_prime(&rsa.prime1, &rsa.prime2, &rsa.modulus);
	f_n = ((uint64_t)(rsa.prime1 - 1) * (uint64_t)(rsa.prime2 - 1));
	rsa.priexpo = mul_inv(rsa.pubexpo, f_n);
	rsa.expo1 = rsa.priexpo % (rsa.prime1 - 1);
	rsa.expo2 = rsa.priexpo % (rsa.prime2 - 1);
	rsa.coef = mul_inv(rsa.prime2, rsa.prime1);
	construct_base64_message(&rsa);
	free_rsa_struct(&rsa);
	return (0);
}

int				get_appropriate_prime(uint32_t *p, uint32_t *q, uint64_t *n)
{
	write(STDERR, "Generating RSA private key, 64 bit long modulus\n", 48);
	while (1)
	{
		*p = prime_gen(*p);
		*q = prime_gen(*q);
		*n = (uint64_t)*p * (uint64_t)*q;
		if (*p == (*n / *q) && (*n >> 63))
			break ;
	}
	write(2, "e is 65537 (0x10001)\n", 21);
	return (0);
}

void			construct_base64_message(t_rsa64bit *rsa)
{
	t_b64_str	base;

	base.pubexpo = construct_int_msg(&rsa->pubexpo, sizeof(rsa->pubexpo));
	base.prime1 = construct_int_msg(&rsa->prime1, sizeof(rsa->prime1));
	base.prime2 = construct_int_msg(&rsa->prime2, sizeof(rsa->prime2));
	base.modulus = construct_int_msg(&rsa->modulus, sizeof(rsa->modulus));
	base.priexpo = construct_int_msg(&rsa->priexpo, sizeof(rsa->priexpo));
	base.expo1 = construct_int_msg(&rsa->expo1, sizeof(rsa->expo1));
	base.expo2 = construct_int_msg(&rsa->expo2, sizeof(rsa->expo2));
	base.coef = construct_int_msg(&rsa->coef, sizeof(rsa->coef));
	base.version = ft_memalloc(3);
	base.version[0] = 0x2;
	base.version[1] = 0x1;
	base.sequence = ft_memalloc(2);
	base.sequence[0] = 0x30;
	base.sequence[1] = base.pubexpo[1] + base.prime1[1] + base.prime2[1] +
	base.modulus[1] + base.priexpo[1] + base.expo1[1] + base.expo2[1] +
	base.coef[1] + base.version[1] + 18;
	rsa->base64 = concatinate_b64_msg(base, base.sequence[1] + 2);
	rsa->msg = base64_encode(rsa->base64, base.sequence[1] + 2);
	print_prikey_rsa_message(rsa, (((base.sequence[1] + 2) + 2) / 3) * 4);
	free_base64_struct(&base);
}

uint8_t			*concatinate_b64_msg(t_b64_str base, size_t size)
{
	uint8_t		*msg;

	msg = ft_memalloc(size);
	ft_memcpy(msg, base.sequence, 2);
	ft_memcpy(msg + 2, base.version, base.version[1] + 2);
	ft_memcpy(msg + 4 + base.version[1], base.modulus, base.modulus[1] + 2);
	ft_memcpy(msg + 6 + base.version[1] + base.modulus[1], base.pubexpo,
	base.pubexpo[1] + 2);
	ft_memcpy(msg + 8 + base.version[1] + base.modulus[1] + base.pubexpo[1],
	base.priexpo, base.priexpo[1] + 2);
	ft_memcpy(msg + 10 + base.version[1] + base.modulus[1] + base.pubexpo[1] +
	base.priexpo[1], base.prime1, base.prime1[1] + 2);
	ft_memcpy(msg + size - (8 + base.coef[1] + base.expo2[1] + base.expo1[1] +
	base.prime2[1]), base.prime2, base.prime2[1] + 2);
	ft_memcpy(msg + size - (6 + base.coef[1] + base.expo2[1] + base.expo1[1]),
	base.expo1, base.expo1[1] + 2);
	ft_memcpy(msg + size - (4 + base.coef[1] + base.expo2[1]),
	base.expo2, base.expo2[1] + 2);
	ft_memcpy(msg + size - (2 + base.coef[1]), base.coef, base.coef[1] + 2);
	return (msg);
}

void			print_prikey_rsa_message(t_rsa64bit *rsa, size_t size)
{
	write(rsa->outfile, "-----BEGIN RSA PRIVATE KEY-----\n", 32);
	print_base64_msg(rsa->outfile, rsa->msg, size);
	write(rsa->outfile, "-----END RSA PRIVATE KEY-----\n", 30);
}
