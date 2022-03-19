NAME	 	= minishell

LDFLAGS		= -L/usr/local/opt/readline/lib
CPPFLAGS	= -I/usr/local/opt/readline/include

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRCS_DIR	= ./src
OBJS_DIR 	= ./obj

SRCS		= readline.c

OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)

INCLUDES	= -Iincludes

all:	$(NAME)

$(NAME): $(OBJS) main.c
		$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) $(INCLUDES) main.c $(OBJS) -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(INCLUDES) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM)  $(NAME)

re:		fclean all

.PHONY: all run clean