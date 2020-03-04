/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:01:08 by mboulara          #+#    #+#             */
/*   Updated: 2019/10/21 10:37:40 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*stdjoin(char *des, char *src)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*ret;

	i = ft_strlen(des);
	j = ft_strlen(src);
	len = i + j;
	ret = ft_strnew(len);
	ft_memcpy(ret, des, i);
	ft_memcpy(ret + i, src, j);
	return (ret);
}
