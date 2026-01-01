# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cress <cress@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/19 16:52:40 by amonteag          #+#    #+#              #
#    Updated: 2025/08/06 22:33:33 by cress            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rsc
RM = rm -f

SRC =	ft_atoi.c ft_isalpha.c ft_itoa.c ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlcpy.c ft_strnstr.c ft_tolower.c \
ft_bzero.c ft_isascii.c ft_memchr.c ft_memset.c ft_putstr_fd.c ft_striteri.c ft_strlen.c ft_strrchr.c ft_toupper.c \
ft_calloc.c ft_isdigit.c ft_memcmp.c ft_putchar_fd.c ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c \
ft_isalnum.c ft_isprint.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcat.c ft_strncmp.c ft_substr.c \
ft_fmt.c ft_printf.c ft_putnbr_hex_fd.c ft_putnbr_xxx_fd.c ft_putunsig_fd.c ft_putptr_hex_fd.c ft_putptr_fd.c\
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_strcmp.c get_netx_line.c ft_count.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@echo "	Creando $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Creando $(NAME)"
	@$(AR) $(NAME) $(OBJ)

clean:
	@echo "Limpiando objs from $(NAME)"
	@$(RM) $(OBJ)

fclean: clean
	@echo "Limpiando todo from $(NAME)"
	@$(RM) $(NAME)

re: fclean all
