NAME	 	= minishell

LDFLAGS		= -L/usr/local/opt/readline/lib
CPPFLAGS	= -I/usr/local/opt/readline/include

CC			= gcc -Wall -Wextra -Werror
CCD			= gcc -Wall -Wextra -Werror -fsanitize=address -g3


RM			= rm -rf

SRCS_DIR	= ./src
OBJS_DIR 	= ./obj

SRCS		=	executor.c shellsignals.c ft_utils.c ft_utils2.c ft_utils3.c \
				bi_cd.c bi_echo.c bi_env.c bi_exit.c bi_export.c bi_pwd.c bi_unset.c \
				exe_pipe_cmds.c exe_heredoc.c heredocsignals.c exe_redir.c exe_builtins.c\
				exe_redirections.c exe_children.c exe_commands.c \
				prs_decide_token.c prs_mini_lexer.c prs_mini_yacc.c prs_process_buffer.c \
				ult_mini_getenv.c utl_free_str_array.c utl_get_env_array.c utl_init_mini.c \
				utl_key_value_split.c utl_strncmp.c utl_join_key_value.c utl_move_fd.c utl_env_array.c\
				utl_set_env.c free_list.c \

OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)


LIB			= -Llibft -lft -lreadline
INCLUDES	= -Iincludes -Ilibft

VALGRIND = valgrind --tool=memcheck \
					--leak-check=full \
					--leak-resolution=high \
					--track-origins=yes \
					--show-reachable=yes \
					--log-file=valgrind.log \

all:	$(NAME)

$(NAME): $(OBJS) main.c libft/libft.a
		@$(CC)  main.c $(OBJS) $(LDFLAGS) $(CPPFLAGS) $(INCLUDES) $(LIB) -o $@
		@echo "$(GREEN)Compiled $@ successfully $(RESET)"

libft/libft.a :
		@make -C libft

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(INCLUDES) $(CPPFLAGS) -c $< -o $@


t: all
	$(VALGRIND) ./minishell -c "cat $$USER"

clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(RED)Removed $(NAME) .obj$(RESET)"

fclean: clean
	@$(RM)  $(NAME)
	@echo "$(RED)Removed $(NAME)$(RESET)"
	
re:		fclean all

.PHONY: all run clean fclean t

# Colors are great!
# Formats are greater!
# https://misc.flogisoft.com/bash/tip_colors_and_formatting
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[033m
BLUE	= \033[034m
PINK	= \033[035m
TEAL	= \033[036m
WHITE	= \033[037m
RESET	= \033[0m # No Color
