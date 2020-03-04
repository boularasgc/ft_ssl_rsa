/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_rsa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 00:54:48 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 20:11:16 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"

void	free_rsa_struct(t_rsa64bit *rsa)
{
	if (rsa->base64)
		free_string_len((char *)rsa->base64,
	ft_strlen((const char *)rsa->base64));
	if (rsa->rfile > STDERR)
		close(rsa->rfile);
	if (rsa->outfile > STDERR)
		close(rsa->outfile);
	if (rsa->msg)
		ft_strdel(&rsa->msg);
	if (rsa->filename1)
		ft_strdel(&rsa->filename1);
	if (rsa->filename2)
		ft_strdel(&rsa->filename2);
	if (rsa->filename3)
		ft_strdel(&rsa->filename3);
}

void	free_base64_struct(t_b64_str *base)
{
	free_string_len((char *)base->sequence, 2);
	free_string_len((char *)base->version, 3);
	free_string_len((char *)base->modulus, base->modulus[1] + 2);
	free_string_len((char *)base->pubexpo, base->pubexpo[1] + 2);
	free_string_len((char *)base->priexpo, base->priexpo[1] + 2);
	free_string_len((char *)base->prime1, base->prime1[1] + 2);
	free_string_len((char *)base->prime2, base->prime2[1] + 2);
	free_string_len((char *)base->expo1, base->expo1[1] + 2);
	free_string_len((char *)base->expo2, base->expo2[1] + 2);
	free_string_len((char *)base->coef, base->coef[1] + 2);
}
