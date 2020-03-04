/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:48:50 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/23 16:46:19 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_rsa.h"

uint32_t	prime_gen(uint32_t p)
{
	ft_urandom(&p, sizeof(p));
	write(STDERR, ".", 1);
	if (!(p & 1))
		p |= 1;
	if (!(p & 0x80000000))
		p |= 0x80000000;
	if (ft_ssl_is_prime(p))
	{
		write(STDERR, "+\n", 2);
		return (p);
	}
	return (prime_gen(p));
}
