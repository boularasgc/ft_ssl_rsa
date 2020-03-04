/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 09:13:06 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/21 21:56:07 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"
#include "ft_ssl.h"

void					print_ascci_char(int fd, int i, size_t size,
const unsigned char *p)
{
	int					j;

	j = 0;
	ft_fprintf(fd, "  ");
	while (j < 16 && j + i < (int)size)
	{
		if (*(p + size - 1 - j) >= 32 && *(p + size - 1 - j) < 127)
			ft_fprintf(fd, "%c", p[size - 1 - j]);
		else
			ft_fprintf(fd, ".");
		j++;
	}
}

void					ft_hexdump(int fd, void *addr, size_t size)
{
	int					i;
	int					j;
	const unsigned char *p;

	p = addr;
	i = 0;
	while (i < (int)size)
	{
		j = 0;
		ft_fprintf(fd, "%04x - ", i);
		while ((j < 16) && ((i + j) < (int)size))
		{
			ft_fprintf(fd, "%02x", p[size - 1 - j]);
			if (j == 7)
				ft_fprintf(fd, "-");
			else
				ft_fprintf(fd, " ");
			j++;
		}
		while (j++ < 16)
			ft_fprintf(fd, "   ");
		print_ascci_char(fd, i, size, &*p);
		ft_fprintf(fd, "\n");
		i += 16;
	}
}
