###########################################
#             VARIABLES                   #
###########################################

NAME		= minishell
OBJ_DIR		= obj
INCLUDES	= -I. -I$(LIBFT_DIR)
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
SRC			=	commands/built_in_cd.c		\
				commands/built_in_echo.c	\
				commands/built_in_exit.c	\
				commands/built_in_export.c	\
				commands/built_ins.c		\
				commands/commands.c			\
				commands/expansions.c		\
				commands/heredoc_loop.c		\
				commands/parse_steps.c		\
				commands/parsers.c			\
				commands/redirect_heredoc.c	\
				commands/redirect.c			\
				execve/execution.c			\
				fsm/error_handler.c			\
				fsm/fsm.c					\
				fsm/state_dquote.c			\
				fsm/state_end.c				\
				fsm/state_error.c			\
				fsm/state_pipe.c			\
				fsm/state_redirect.c		\
				fsm/state_squote.c			\
				fsm/state_start.c			\
				fsm/state_word.c			\
				pipex/cmd_execution.c		\
				pipex/pipeline.c			\
				prompt/init.c				\
				prompt/prompt.c				\
				signals/signal.c			\
				utils/cd_utils.c			\
				utils/execve_utils.c		\
				utils/expansion_utils.c		\
				utils/export_utils.c		\
				utils/free.c				\
				utils/fsm_utils.c			\
				utils/heredoc_utils.c		\
				utils/main_loop_order.c		\
				utils/signal_utils.c		\
				utils/token_utils.c			\
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