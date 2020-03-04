/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 14:07:25 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/21 20:25:34 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BASE64_H
# define FT_BASE64_H

# include <stdlib.h>
# include <stdint.h>
# include "libft/libft.h"

typedef	struct		s_b64_d
{
	uint8_t			bytes[4];
	size_t			lastfour;
	size_t			i;
	size_t			j;
	uint8_t			*msg;
	uint8_t			byte;
}					t_b64_d;

#endif
