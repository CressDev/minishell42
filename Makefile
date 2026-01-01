# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cress <cress@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/20 10:19:55 by cress             #+#    #+#              #
#    Updated: 2026/01/01 11:11:35 by cress            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = minishell
SRC_MS =main.c read_line.c readline2.c commands.c commands_parse.c free_mem.c tokenizer.c tokenizer2.c tokenizer_utils.c quote_processor.c built_ins.c built_in_export.c built_in_cd.c built_in_exit.c execve.c redirect.c redirect_heredoc.c prompt.c redirect_parse.c redirect_parse2.c signal_handler.c signal_handler_utils.c signal_handler_utils2.c pipex.c pipex2.c pipex_parse.c expansions.c expansions2.c utils.c
OBJ_MS = $(SRC_MS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_MS)
	@echo "Creando $(NAME)"
	@$(CC) $(CFLAGS) $(OBJ_MS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@echo "Creando $(LIBFT)"
	@make -s -C $(LIBFT_DIR) all

%.o: %.c
	@echo "Creando $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Limpiando objs from $(NAME)"
	@$(RM) $(OBJ_MS)
	@make -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Limpiando todo from $(NAME)"
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_DIR) fclean

re: fclean all
