/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_private.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 19:34:52 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/08 21:42:09 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"

int				get_rsa_values(t_rsa64bit *rsa)
{
	int			i;

	rsa->sequence = rsa->sequence << 8 | rsa->base64[0];
	rsa->sequence = rsa->sequence << 8 | rsa->base64[1];
	i = 2;
	rsa->version = extract_value(&(*rsa->base64), &i);
	rsa->modulus = extract_value(&(*rsa->base64), &i);
	rsa->pubexpo = extract_value(&(*rsa->base64), &i);
	rsa->priexpo = extract_value(&(*rsa->base64), &i);
	rsa->prime1 = extract_value(&(*rsa->base64), &i);
	rsa->prime2 = extract_value(&(*rsa->base64), &i);
	rsa->expo1 = extract_value(&(*rsa->base64), &i);
	rsa->expo2 = extract_value(&(*rsa->base64), &i);
	rsa->coef = extract_value(&(*rsa->base64), &i);
	return (0);
}

int				get_pbk_values(t_rsa64bit *rsa)
{
	int			i;

	i = 22;
	rsa->modulus = extract_value(&(*rsa->base64), &i);
	rsa->pubexpo = extract_value(&(*rsa->base64), &i);
	return (0);
}

uint64_t		extract_value(uint8_t *msg, int *i)
{
	int			leni;
	int			var1;
	uint64_t	s;

	var1 = msg[*i + 1];
	leni = msg[*i + 1];
	*i += 2;
	s = 0;
	while (leni-- > 0)
		s = s << 8 | msg[(*i)++];
	return (s);
}
