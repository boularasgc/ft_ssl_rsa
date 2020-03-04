/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rsa.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:27:41 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 08:43:40 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RSA_H
# define FT_RSA_H
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define RSA_PHEADER "-----BEGIN RSA PRIVATE KEY-----"
# define RSA_PFOOTER "-----END RSA PRIVATE KEY-----"
# define RSA_PBHEADER "-----BEGIN PUBLIC KEY-----"
# define RSA_PBFOOTER "-----END PUBLIC KEY-----"

# include <stdlib.h>
# include <stdint.h>
# include "libft/libft.h"

typedef	struct	s_rsa64bit
{
	uint16_t	sequence;
	uint8_t		version;
	uint64_t	modulus;
	uint32_t	pubexpo;
	uint64_t	priexpo;
	uint32_t	prime1;
	uint32_t	prime2;
	uint32_t	expo1;
	uint32_t	expo2;
	uint32_t	coef;
	uint8_t		*base64;
	char		*msg;
	int			rfile;
	int			outfile;
	char		*filename1;
	char		*filename2;
	char		*filename3;
}				t_rsa64bit;

typedef	struct	s_mod_inv
{
	__int128_t	t;
	__int128_t	nt;
	__int128_t	r;
	__int128_t	nr;
	__int128_t	q;
	__int128_t	tmp;
}				t_mod_inv;

typedef struct	s_b64_str
{
	uint8_t		*sequence;
	uint8_t		*version;
	uint8_t		*modulus;
	uint8_t		*pubexpo;
	uint8_t		*priexpo;
	uint8_t		*prime1;
	uint8_t		*prime2;
	uint8_t		*expo1;
	uint8_t		*expo2;
	uint8_t		*coef;
}				t_b64_str;

typedef	enum	e_rsa_flags
{
	c_F = 1,
	hxdmp_F = 1,
	n_F = 2,
	m_F = 4,
	enc_F = 4,
	in_F = 8,
	out_F = 16,
	pbin_F = 32,
	pbout_F = 64,
	dec_F = 64,
	t_F = 128,
}				t_rsa_flags;

typedef	struct	s_rsa_cmds
{
	char		*cmd_name;
	t_rsa_flags	flag;
}				t_rsa_cmds;
typedef struct	s_pbk_str
{
	uint8_t		*sequence;
	uint8_t		*sequence2;
	uint8_t		*obj_id;
	uint8_t		*null_id;
	uint8_t		*bit_str;
	uint8_t		*sequence3;
	uint8_t		*modulus;
	uint8_t		*pubexpo;
}				t_pbk_str;

int				ft_ssl_is_prime(uint64_t n);
uint32_t		prime_gen(uint32_t p);
int				get_appropriate_prime(uint32_t *p, uint32_t *q, uint64_t *n);
uint64_t		mul_inv(uint64_t a, uint64_t b);
void			construct_base64_message(t_rsa64bit *rsa);
void			copy_indianese(void *src, void *dest, size_t s_sz, size_t d_sz);
size_t			get_integer_length(void *p, size_t sz);
uint8_t			*construct_int_msg(void *p, size_t size);
uint8_t			*concatinate_b64_msg(t_b64_str base, size_t size);
char			*base64_encode(uint8_t *buf, size_t size);
uint8_t			*base_64_decoder(char *str, size_t len);
void			print_base64_msg(int fd, char *msg, size_t size);
void			print_prikey_rsa_message(t_rsa64bit *rsa, size_t size);
int				genrsa(void);
uint64_t		mul_inv(uint64_t a, uint64_t b);
void			print_rsa_values(t_rsa64bit rsa);
uint64_t		extract_value(uint8_t *msg, int *i);
int				get_rsa_values(t_rsa64bit *rsa);
int				check_base64_format(char *str, size_t len);
int				read_rsa_file(int fd, char **str, const char *h, const char *f);
int				rsa_file_cnt(int fd, t_rsa64bit *rsa, uint8_t flag);
size_t			get_bit_length(void *p, size_t sz);
void			rsa_commands_cases(const char *argv[], uint8_t *flag, int *i,
				t_rsa64bit *rsa);
int				parse_rsa_commands(int c, char const *argv[], t_rsa64bit *rsa);
int				rsa_file_select(t_rsa64bit *rsa, uint8_t flag);
int				open_rsaoutput_file(t_rsa64bit *rsa);
int				print_rsa_info(t_rsa64bit rsa, uint8_t flag);
void			print_pkey_info(t_rsa64bit rsa, uint8_t flag);
char			*rsa_checker(t_rsa64bit rsa);
uint8_t			*constrcut_pubkey(t_rsa64bit rsa);
uint8_t			*concatinate_pbk_msg(t_pbk_str *b, size_t size);
uint8_t			*object_id_func(void);
int				get_pbk_values(t_rsa64bit *rsa);
void			print_pubkey_rsa_message(t_rsa64bit *rsa, size_t size);
uint64_t		mul_mod(uint64_t a, uint64_t b, uint64_t m);
size_t			mod_power(size_t value, size_t exponent, size_t mod);
size_t			rsautl_encrypt(uint8_t *buff, size_t size, size_t e, size_t n);
size_t			rsautl_decrypt(uint8_t *buff, size_t size, size_t d, size_t n);
void			hexdump(void *addr, size_t size);
void			print_rsautl(int fd, uint64_t encrypted, uint8_t flag);
void			print_rev_buffer(int fd, void *p, size_t size);
int				rsautl_readfile(uint8_t flag, t_rsa64bit *rsa, char **line);
uint8_t			parse_rsautl_args(int c, const char *argv[], t_rsa64bit *rsa);
uint8_t			rsautl_cmnds_cases(const char *argv[], int *i, t_rsa64bit *rsa);
int				rsautl_execute(uint8_t flag, t_rsa64bit *rsa);
void			free_rsa_struct(t_rsa64bit *rsa);
void			free_base64_struct(t_b64_str *base);
#endif
