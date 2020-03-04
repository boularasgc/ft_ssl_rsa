/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 08:09:59 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 08:11:05 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	rotate_left(uint32_t a, uint32_t b)
{
	return (((a) << (b)) | ((a) >> (32 - (b))));
}

uint32_t	rotate_right(uint32_t a, uint32_t b)
{
	return (((a) >> (b)) | ((a) << (32 - (b))));
}

uint32_t	ch_(uint32_t x, uint32_t y, uint32_t z)
{
	return (((x) & (y)) ^ (~(x) & (z)));
}

uint32_t	maj_(uint32_t x, uint32_t y, uint32_t z)
{
	return (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)));
}

uint32_t	ep0_(uint32_t x)
{
	return (rotate_right(x, 2) ^ rotate_right(x, 13) ^ rotate_right(x, 22));
}
