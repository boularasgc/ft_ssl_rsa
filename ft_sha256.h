/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 09:43:07 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 08:01:09 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

typedef	struct	s_256ctx
{
	uint8_t		*msg;
	uint32_t	state[8];
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
	uint32_t	w[64];
	size_t		ini_len;
	size_t		newlen;
}				t_256ctx;

void			construct_sha256_mssg(t_cx data, t_256ctx *h);
void			print_256_message(t_256ctx h, t_cx data);

#endif
