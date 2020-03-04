/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 10:21:25 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/23 15:43:58 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"

int				read_rsa_file(int fd, char **str, const char *header,
const char *footer)
{
	char		*line;
	int			i;

	*str = *str == NULL ? ft_memalloc(100) : *str;
	while ((i = get_next_line(fd, &line)) == 1)
	{
		if (ft_strstr(line, header))
			break ;
	}
	if (i == 0)
		return (0);
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strstr(line, footer))
			break ;
		ft_memcpy(*str + i, line, ft_strlen(line));
		i = i + ft_strlen(line);
	}
	ft_strdel(&line);
	if (!check_base64_format(*str, ft_strlen(*str)))
		return (0);
	return (1);
}

int				rsa_file_cnt(int fd, t_rsa64bit *rsa, uint8_t flag)
{
	int			i;
	const char	*header;
	const char	*footer;

	header = (flag & pbin_F) ? RSA_PBHEADER : RSA_PHEADER;
	footer = (flag & pbin_F) ? RSA_PBFOOTER : RSA_PFOOTER;
	i = read_rsa_file(fd, &rsa->msg, header, footer);
	if (i)
	{
		rsa->base64 = base_64_decoder(&(*rsa->msg), ft_strlen(rsa->msg));
		i = (flag & pbin_F) ? get_pbk_values(rsa) : get_rsa_values(rsa);
	}
	else
	{
		ft_fprintf(STDERR, "Cannot load key or not exist.\n");
		exit(1);
	}
	return (1);
}

int				rsa_file_select(t_rsa64bit *rsa, uint8_t flag)
{
	int			fd;

	fd = (flag & in_F) ? open(rsa->filename1, O_RDONLY) : STDIN;
	if (fd >= 0)
		rsa_file_cnt(fd, &(*rsa), flag);
	else if (fd == -1)
	{
		ft_putstr_fd("Cannot open file. Try again later.\n", STDERR);
		exit(1);
	}
	return (0);
}
