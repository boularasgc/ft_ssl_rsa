# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 12:30:59 by mboulara          #+#    #+#              #
#    Updated: 2020/01/22 08:13:36 by mboulara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          =   gcc
CFLAGS      =   -Wall -Wextra   -Werror 

# — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

NAME        =   ft_ssl

LIBRARY     =  	./libft/libft.a											  \

SOURCES     =   ft_ssl.c                                                    \
                ft_stdjoin.c												\
				hash_parser.c												\
				md5.c														\
				read_fd.c													\
				sha256.c													\
				sha256_ext.c												\
				str_handler.c												\
				hash_print.c												\
				sha224.c													\
				sha224_ext.c												\
				prime_checker.c												\
				ft_ssl_is_prime.c											\
				genrsa.c\
				genrsa_util.c\
				prime_gen.c\
				genrsa_parser.c\
				base_64_encode.c\
				base_64_decode.c\
				mod_inverse.c\
				rsa_parser.c\
				extract_private.c\
				rsa_file.c\
				rsa_printfuncs.c\
				constrcut_pubkey.c\
				rsautl_parser.c\
				rsautl_encrypt.c\
				ft_hexdump.c \
				free_rsa.c\
				help_functions1.c\
				help_functions2.c\
				
OBJECTS     =   $(SOURCES:.c=.o)

# — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

all: $(NAME)

debug: CFLAGS += -g -O0 -fsanitize=address
debug: $(NAME)

$(NAME): $(LIBRARY) $(OBJECTS)
	@$(CC) $(CFLAGS) $(LIBRARY) $(OBJECTS) -o $@
	@chmod +x $(NAME)
	@echo && echo $(GREEN) "[√]     [Program Successfully Compiled!]" && echo

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(WHITE) "Compiling => " $<

$(LIBRARY):
	@make -C libft/

# — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

DEL  =  /bin/rm -rf

clean:
	@$(DEL) $(shell find . -name '*.[o]')

fclean: clean
	@$(DEL) $(NAME) $(shell find . -name '*.[a]')

re: fclean all

# — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

nc:
	@echo && echo $(GREEN) "Checking Norme -- Source Files:" && echo $(WHITE);
	@norminette $(shell find . -name '*.c')

nh:
	@echo && echo $(GREEN) "Checking Norme -- Header Files:" && echo $(WHITE);
	@norminette $(shell find . -name '*.h')

na: nh nc

# — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

GREEN =  "\033[1;32m"
WHITE =  "\033[1;37m"

# Correction Script — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

correction:

	@echo '==============================================================='
	@echo && echo $(GREEN) "I - Checking Author File:" && echo $(WHITE);
	@sleep 1
	cat author
	@echo
	@sleep 1

	@echo '==============================================================='
	@echo && echo $(GREEN) "II - Checking Norme:" && echo $(WHITE);
	@sleep 1

	@echo && echo $(GREEN) "a - Checking Norme -- Header Files:" && echo $(WHITE);
	@sleep 1
	@norminette $(shell find . -name '*.h')

	@sleep 1
	@echo && echo $(GREEN) "b - Checking Norme -- Source Files:" && echo $(WHITE);
	@sleep 1
	@norminette $(shell find . -name '*.c')
	@echo

	@echo '==============================================================='
	@sleep 1
	@echo && echo $(GREEN) "III - Checking Compilation:" && echo $(WHITE);
	@sleep 1
	@echo 'make all'
	@echo
	@sleep 1
	@make all
	@sleep 1
	@sleep 1

	@echo '==============================================================='
	@echo && echo $(GREEN) "IV - Checking Makefile Rules:" && echo $(WHITE);
	@sleep 1
	@echo 'Current working directory:'
	@echo
	@sleep 1
	@echo 'ls -1'
	@echo
	@sleep 1
	@ls -1
	@echo
	@sleep 1

	@echo '==============================================================='
	@echo && echo $(GREEN) "a - make clean" && echo $(WHITE);
	@sleep 1
	@echo 'make clean'
	@echo
	@make clean
	@sleep 1
	@sleep 1
	@ls -1
	@echo
	@sleep 1

	@echo '==============================================================='
	@echo && echo $(GREEN) "b - make fclean" && echo $(WHITE);
	@sleep 1
	@echo 'make fclean'
	@echo
	@make fclean
	@sleep 1
	@sleep 1
	@ls -1
	@echo
	@sleep 1

	@echo '==============================================================='
	@echo && echo $(GREEN) "V - Explain code/approach" && echo $(WHITE);
	@echo $(GREEN) "VI - Q&A" && echo $(WHITE);
	@echo '==============================================================='

# — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

.PHONY: all clean fclean re nc nh na