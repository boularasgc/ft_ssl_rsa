/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_is_prime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:12:13 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/13 17:04:58 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "ft_rsa.h"

uint64_t		mul_mod(uint64_t a, uint64_t b, uint64_t m)
{
	uint64_t	res;
	uint64_t	temp_b;

	res = 0;
	if (b >= m)
		b = (m > UINT64_MAX / 2u) ? b - m : b % m;
	while (a != 0)
	{
		if (a & 1)
		{
			if (b >= m - res)
				res -= m;
			res += b;
		}
		a >>= 1;
		temp_b = b;
		if (b >= m - b)
			temp_b -= m;
		b += temp_b;
	}
	return (res);
}

size_t			mod_power(size_t value, size_t exponent, size_t mod)
{
	size_t		power;
	size_t		result;

	result = 1;
	power = value;
	while (exponent > 0)
	{
		if ((exponent & 1) == 1)
			result = mul_mod(result, power, mod);
		power = mul_mod(power, power, mod);
		exponent >>= 1;
	}
	return ((size_t)result);
}

int				witness(size_t n, size_t s, size_t d, size_t a)
{
	size_t		x;
	size_t		y;

	x = mod_power(a, d, n);
	while (s)
	{
		y = mul_mod(x, x, n);
		if (y == 1 && x != 1 && x != n - 1)
			return (0);
		x = y;
		--s;
	}
	if (y != 1)
		return (0);
	return (1);
}

int				ft_ssl_is_prime_extended(size_t n, size_t s, size_t d)
{
	if (n < 1373653)
		return (witness(n, s, d, 2) && witness(n, s, d, 3));
	else if (n < 9080191)
		return (witness(n, s, d, 31) && witness(n, s, d, 73));
	else if (n < 4759123141)
		return (witness(n, s, d, 2) && witness(n, s, d, 7) &&
					witness(n, s, d, 61));
	else if (n < 1122004669633)
		return (witness(n, s, d, 2) && witness(n, s, d, 13) &&
					witness(n, s, d, 23) && witness(n, s, d, 1662803));
	else if (n < 2152302898747)
		return (witness(n, s, d, 2) && witness(n, s, d, 3) &&
	witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11));
	else if (n < 3474749660383)
		return (witness(n, s, d, 2) && witness(n, s, d, 3) &&
	witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11)
	&& witness(n, s, d, 13));
		return (witness(n, s, d, 2) && witness(n, s, d, 3)
	&& witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) &&
	witness(n, s, d, 13) && witness(n, s, d, 17));
}

int				ft_ssl_is_prime(uint64_t n)
{
	size_t		d;
	size_t		s;

	if (((!(n & 1)) && n != 2) || (n < 2) || (n % 3 == 0 && n != 3))
		return (0);
	if (n <= 3)
		return (1);
	d = n / 2;
	s = 1;
	while (!(d & 1))
	{
		d /= 2;
		++s;
	}
	return (ft_ssl_is_prime_extended(n, s, d));
}

/*
**This test is based on Miller-Rabin algorithm for checking primality.
*/
