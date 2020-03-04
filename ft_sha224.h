/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha224.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:59:16 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 08:40:55 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA224_H
# define FT_SHA224_H

typedef	struct	s_224ctx
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
}				t_224ctx;

void			construct_sha224_mssg(t_cx data, t_224ctx *h);
void			print_224_message(t_224ctx h, t_cx data);
#endif
