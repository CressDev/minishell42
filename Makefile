# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cress <cress@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/20 10:19:55 by cress             #+#    #+#              #
#    Updated: 2026/01/18 09:00:11 by cress            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###########################################
#             VARIABLES                   #
###########################################

NAME		= minishell
OBJ_DIR		= obj
INCLUDES	= -I. -I$(LIBFT_DIR)
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
SRC			=	commands/built_in_cd.c			\
				commands/built_in_echo.c		\
				commands/built_in_exit.c		\
				commands/built_in_export.c		\
				commands/built_in_export_utils.c\
				commands/built_ins.c			\
				commands/commands.c				\
				commands/expansions.c			\
				commands/parsers.c				\
				commands/redirect_heredoc.c		\
				commands/redirect.c				\
				commands/utils.c				\
				commands/utils2.c				\
				commands/utils3.c				\
				commands/utils4.c				\
				commands/utils5.c				\
				commands/fsm_args_helper.c		\
				execve/execution.c				\
				execve/utils.c					\
				fsm/error_handler.c				\
				fsm/fsm_utils.c					\
				fsm/fsm.c						\
				fsm/state_dquote.c				\
				fsm/state_end.c					\
				fsm/state_error.c				\
				fsm/state_pipe.c				\
				fsm/state_redirect.c			\
				fsm/state_squote.c				\
				fsm/state_start.c				\
				fsm/state_word.c				\
				fsm/token_utils.c				\
				pipex/cmd_execution.c			\
				pipex/pipeline.c				\
				prompt/init.c					\
				prompt/prompt.c					\
				signals/signal_handler_utils.c	\
				signals/signal_handler_utils2.c	\
				signals/signal_handler.c		\
				utils/free.c					\
				utils/utils.c					\
				main.c
OBJ			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -O0

###########################################
#                 RULES                   #
###########################################

all: $(NAME) $(LIBFT)

$(LIBFT):
	@echo "Compiled libft"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1

$(NAME): $(OBJ) $(LIBFT)
	@echo "Compiled minishell"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

###########################################
#               CLEANING                  #
###########################################

clean:
	@echo "Removing object files"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null 2>&1

fclean: clean
	@echo "Removing executables"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re pipes