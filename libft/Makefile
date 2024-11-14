# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/19 16:24:19 by mgavorni          #+#    #+#              #
#    Updated: 2023/11/19 16:24:23 by mgavorni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -c

SOURCES = 	ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strjoin.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_split.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_substr.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_strnstr.c \
			ft_strtrim.c \
			ft_strdup.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memchr.c \
			ft_calloc.c \
			ft_strlcpy.c \
			ft_itoa.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memcmp.c \
			ft_strlcat.c

SOURCES_B = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstclear.c \
			ft_lstmap.c

OBJECTS = ${SOURCES:.c=.o}

OBJECTS_B = ${SOURCES_B:.c=.o}

NAME = libft.a


all: ${NAME}

.c.o:
	cc $(CFLAGS) $< -o ${<:.c=.o}

${NAME}: ${OBJECTS}
	ar rcs ${NAME} ${OBJECTS}

bonus: ${OBJECTS_B}
	ar rcs ${NAME} ${OBJECTS_B}

clean:
	rm -f ${OBJECTS}
	rm -f ${OBJECTS_B}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all, bonus, clean, fclean, re