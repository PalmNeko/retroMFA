# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tookuyam <tookuyam@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 17:19:34 by tookuyam          #+#    #+#              #
#    Updated: 2023/11/09 14:34:28 by tookuyam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = retromfa
CC = cc
CFLAGS += -Wall -Wextra -Werror
CFLAGS += -MP -MMD -g -O0
CFLAGS += -I src/includes -I src/mlx
LINKFLAGS = $(CFLAGS) -L./src/mlx -lmlx -framework OpenGL -framework AppKit
SRCS = \
	src/main.c src/modules/view_mfa.c
OBJS = $(SRCS:.c=.o)
DEPENDS = $(SRCS:.c=.d)

all: $(NAME) $(BONUS_RULE)

-include $(DEPENDS)

$(NAME): src/mlx/libmlx.a $(OBJS)
	$(CC) $(OBJS) $(LINKFLAGS) -o $(NAME)

src/mlx/libmlx.a:
	make --directory src/mlx

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install:

clean:
	find . -name "*.out" -delete
	find . -name "*.d" -delete
	find . -name "*.o" -delete
	find . -name "*.a" -delete

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
