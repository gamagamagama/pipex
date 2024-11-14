# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matus <matus@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/28 14:08:39 by mgavorni          #+#    #+#              #
#    Updated: 2024/11/13 22:55:50 by matus            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -c

SOURCES = $(wildcard *.c)
# SOURCES = ft_printf.c \
# 		  ft_print_input.c \
# 		  ft_print_hex.c \
# 		  ft_print_ptr.c \
# 		  ft_adrr.c \
# 		  ft_print_uint.c \
# 		  ft_print_int.c \
# 		  ft_unint.c \
# 		  ft_uint_len.c \
# 		  ft_putnbr_fd.c \
# 		  ft_print_str.c \
# 		  ft_print_char.c \
# 		  ft_putchar_fd.c \
# 		  ft_putstr.c
		 


OBJECTS = ${SOURCES:.c=.o}

NAME = libftprintf.a


all: ${NAME}

.c.o:
	cc $(CFLAGS) $< -o ${<:.c=.o}

${NAME}: ${OBJECTS}
	ar rcs ${NAME} ${OBJECTS}

clean:
	rm -f ${OBJECTS}
	

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all, clean, fclean, re