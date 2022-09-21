# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/13 14:03:17 by ael-korc          #+#    #+#              #
#    Updated: 2022/09/20 17:07:09 by ael-korc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d

HEADER = cub3d.h\
		gnl/get_next_line.h\
		libft/libft.h\

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Ofast -Os
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

SRCS = cub3d.c \
	readmap.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c \
	init.c draw.c checks.c raycasting.c parsing.c utils.c\
	

OBJS = $(SRCS:.c=.o)

all: $(NAME) clean
	
$(NAME): $(OBJS) $(LIBFT_LIB) $(HEADER) 
	$(CC) $(CFLAGS) $(MLXFLAGS) $(LIBFT_LIB) $(OBJS) -o $(NAME)
	

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

	
clean:
	rm -rf $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	clear

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT_LIB)

re: fclean all
.PHONY: all clean fclean re bonus
