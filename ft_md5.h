/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:14:12 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/21 23:50:13 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <stdint.h>
# include <stdlib.h>
# include "ft_ssl.h"

typedef	struct			s_ctx
{
	uint8_t				*msg;
	uint32_t			state[4];
	uint32_t			*w;
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
	uint32_t			f;
	uint32_t			g;
	uint32_t			temp;
	uint64_t			len;
	size_t				ini_len;
	size_t				newlen;
}						t_ctx;

int						message_digest_md5(t_cx data);
void					print_md5_message(t_ctx h, t_cx data);

#endif
