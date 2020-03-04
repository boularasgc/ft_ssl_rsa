/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:26:13 by mboulara          #+#    #+#             */
/*   Updated: 2019/12/18 23:33:57 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_rsa.h"

int	prime_checker(const char *argv[])
{
	uint64_t p;

	p = ft_ato64bit(argv[0]);
	if (ft_ssl_is_prime(p))
		ft_printf("%X is prime\n", p);
	else
		ft_printf("%X is not  prime\n", p);
	return (0);
}

int	prime_parser(int argc, const char *argv[], t_cx data, t_cyph_f f)
{
	if (argc > 1)
	{
		ft_printf("too many arguments ,more to be implemented");
		return (0);
	}
	(void)data.file;
	(void)f;
	return (prime_checker(argv));
}
