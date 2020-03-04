/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:39:42 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 10:42:13 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <string.h>

int			stringyfy_file_desc(int fd, char **line)
{
	char	rb[BUFF_SIZE + 1];
	size_t	ret;
	char	*hd;
	char	*ptr;

	if (*line == NULL)
		*line = ft_strdup("");
	hd = ft_strnew(BUFF_SIZE);
	ptr = hd;
	while (((ret = read(fd, rb, BUFF_SIZE)) > 0))
	{
		rb[ret] = '\0';
		hd = stdjoin(hd, rb);
		free_string_len(ptr, ft_strlen(ptr));
		ptr = hd;
	}
	(*line) = hd ? ft_strdup(hd) : ft_strdup("");
	if (hd)
		free_string_len(hd, ft_strlen(hd));
	return (*line != NULL);
}

int			read_stdin(t_cx *data, t_cyph_f f)
{
	data->line = NULL;
	if (s_FLAG & data->flag)
		return (0);
	if (p_FLAG & data->flag)
		return (0);
	if (stringyfy_file_desc(0, (&(data->line))))
	{
		data->flag |= p_FLAG;
		return (f(*data));
	}
	else
		return (0);
	return (1);
}

int			read_file(const char **argv, t_cx *data, t_cyph_f f)
{
	int		i;
	int		fd;
	int		ret;

	ret = 0;
	i = -1;
	(data->flag |= f_FLAG);
	while (argv[++i])
	{
		if ((fd = open(argv[i], O_RDONLY)) > -1)
		{
			if (data->line)
				data->line = NULL;
			stringyfy_file_desc(fd, &data->line);
			data->file = ft_strdup(argv[i]);
			f(*data);
		}
		else
		{
			ft_printf(KRED"%s: %s :No such file or directory\n"RESET,
			data->func_name, argv[i]);
			ret = 1;
		}
	}
	return (ret);
}
