/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 08:11:30 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 08:12:10 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	ep1_(uint32_t x)
{
	return (rotate_right(x, 6) ^ rotate_right(x, 11) ^ rotate_right(x, 25));
}

uint32_t	wj0_(uint32_t x)
{
	return (rotate_right(x, 7) ^ rotate_right(x, 18) ^ ((x) >> 3));
}

uint32_t	wj1_(uint32_t x)
{
	return (rotate_right(x, 17) ^ rotate_right(x, 19) ^ ((x) >> 10));
}
