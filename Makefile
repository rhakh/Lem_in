# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhakh <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/28 15:15:42 by rhakh             #+#    #+#              #
#    Updated: 2017/03/08 19:30:14 by rhakh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC =   main.c \
        algo.c \
        calc_turn.c \
        data_constructor.c \
        data_func.c \
        farm_constructor.c \
        find_room.c \
        find_ways_arr.c \
        init_farm.c \
        init_farm_help.c \
        lst_way.c \
        path_constructor.c \
        validate_data.c \
        walk_by_ways.c \
        way_func.c \

SRCDIR = ./src/

OBJDIR = ./obj/

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

FLAGS = -Wall -Wextra -Werror

all: obj $(NAME)

obj:
	make -C ./new_libft all
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) ./new_libft/libft.a

clean:
	make -C ./new_libft clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make -C ./new_libft fclean
	/bin/rm -f $(NAME)

re: fclean all
