# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 13:17:07 by leu-lee           #+#    #+#              #
#    Updated: 2022/03/20 12:02:50 by leu-lee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
						ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
						ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
						ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
						ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
						ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
						ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

BONUS		=		ft_lstadd_front.c ft_lstadd_back.c ft_lstclear.c ft_lstdelone.c \
						ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(BONUS:.c=.o)

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

NAME		= libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
		ar rcs $(NAME) $(OBJS)

bonus:		$(OBJS) $(OBJS_BONUS)
		ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
		$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re
