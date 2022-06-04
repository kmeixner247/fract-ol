# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 18:07:55 by kmeixner          #+#    #+#              #
#    Updated: 2022/05/16 15:48:38 by kmeixner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol

CC			=	gcc

SRCS		=	fractol.c fractol_utils.c math_utils.c colour_utils.c colourschemes.c \
				zoom.c moveimg.c box.c mandelbrot.c julia.c burningship.c input.c keys.c \
				mouse.c

RM			=	rm

CFLAGS		=	-Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(SRCS)
			$(CC) $(SRCS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
			$(RM) -f $(NAME)

fclean:		clean

re:			fclean all

.PHONY:		all bonus clean fclean re