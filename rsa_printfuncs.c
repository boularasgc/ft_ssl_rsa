/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_printfuncs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 22:08:29 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/21 01:37:02 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rsa.h"

int		print_rsa_info(t_rsa64bit rsa, uint8_t flag)
{
	rsa_file_select(&rsa, flag);
	rsa.outfile = (flag & out_F) ? open_rsaoutput_file(&rsa) : STDOUT;
	if ((flag & pbout_F) && !(flag & pbin_F))
	{
		rsa.base64 = constrcut_pubkey(rsa);
		rsa.msg = base64_encode(rsa.base64, rsa.base64[1] + 2);
	}
	if (flag & t_F)
		print_pkey_info(rsa, flag);
	if (flag & c_F)
		ft_fprintf(rsa.outfile, "%s", rsa_checker(rsa));
	if (flag & m_F)
		ft_fprintf(rsa.outfile, "Modulus=%X\n", rsa.modulus);
	if (!(flag & n_F))
	{
		ft_putstr_fd("writing RSA key\n", STDERR);
		if ((flag & pbout_F) || (flag & pbin_F))
			print_pubkey_rsa_message(&rsa, ft_strlen(rsa.msg));
		else
			print_prikey_rsa_message(&rsa, ft_strlen(rsa.msg));
	}
	if (rsa.outfile > STDERR)
		close(rsa.outfile);
	return (0);
}

void	print_pkey_info(t_rsa64bit rsa, uint8_t flag)
{
	ft_fprintf(rsa.outfile, "Private-Key: (%d bit)\n",
	get_bit_length(&rsa.modulus, sizeof(rsa.modulus)));
	ft_fprintf(rsa.outfile, "modulus: %llu (0x%x)\n", rsa.modulus, rsa.modulus);
	ft_fprintf(rsa.outfile, "publicExponent: %llu (0x%x)\n",
	rsa.pubexpo, rsa.pubexpo);
	if (!(flag & pbin_F))
	{
		ft_fprintf(rsa.outfile, "privateExponent: %llu (0x%x)\n",
		rsa.priexpo, rsa.priexpo);
		ft_fprintf(rsa.outfile, "prime1: %llu (0x%x)\n",
		rsa.prime1, rsa.prime1);
		ft_fprintf(rsa.outfile, "prime2: %llu (0x%x)\n",
		rsa.prime2, rsa.prime2);
		ft_fprintf(rsa.outfile, "exponent1: %llu (0x%x)\n",
		rsa.expo1, rsa.expo1);
		ft_fprintf(rsa.outfile, "exponent2: %llu (0x%x)\n",
		rsa.expo2, rsa.expo2);
		ft_fprintf(rsa.outfile, "coefficient: %llu (0x%x)\n",
		rsa.coef, rsa.coef);
	}
}

int		open_rsaoutput_file(t_rsa64bit *rsa)
{
	int	fd;

	if (!rsa->filename2)
	{
		ft_putstr_fd("file name does not exist to output.\n", STDERR);
		exit(1);
	}
	fd = open(rsa->filename2, O_WRONLY | O_CREAT |
	O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		write(STDERR, "File error, pls try again\n", 26);
		exit(0);
	}
	return (fd);
}
