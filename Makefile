NAME	 	= minishell

LDFLAGS		= -L/usr/local/opt/readline/lib
CPPFLAGS	= -I/usr/local/opt/readline/include

CC			= gcc -Wall -Wextra -Werror -fsanitize=address -g3
RM			= rm -rf

SRCS_DIR	= ./src
GNL_DIR		= ./get_next_line
OBJS_DIR 	= ./obj

SRCS		=	bi_cd.c bi_echo.c bi_env.c bi_export.c bi_ft_exit.c bi_pwd.c bi_unset.c \
				prs_mini_lexer.c prs_mini_yacc.c prs_parser.c \
				ult_mini_getenv.c utl_free_str_array.c utl_get_env_array.c utl_init_mini.c \
				shellsignals.c 

OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)

SRCS_GNL	= get_next_line.c get_next_line_utils.c
OBJS_GNL	= $(SRCS_GNL:%.c=$(OBJS_DIR)/%.o)


LIB			= -Llibft -lft -lreadline
INCLUDES	= -Iincludes -Iget_next_line -Ilibft

all:	$(NAME)

$(NAME): $(OBJS) $(OBJS_GNL) main.c libft/libft.a
		@$(CC) $(LDFLAGS) $(CPPFLAGS) $(INCLUDES) $(LIB) main.c $(OBJS) $(OBJS_GNL) -o $@
		@echo "$(GREEN)Compiled $@ successfully $(RESET)"

libft/libft.a :
		@make -C libft

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(INCLUDES) $(CPPFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(INCLUDES) -c $< -o $@

t: all
	./minishell

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