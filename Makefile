# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 15:18:52 by cfabian           #+#    #+#              #
#    Updated: 2022/02/01 13:27:13 by cfabian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	pipex
SRC 		= 	src
SRCS 		= 	$(SRC)/main.c $(SRC)/init.c $(SRC)/free.c
								
OBJ			= 	obj
OBJS		= 	$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
CC			= 	gcc
CFLAGS		= 	-Werror -Wall -Wextra
RM			= 	rm -f
LIB 		=	libft.a
INCLUDES	=	pipex.h

all: $(NAME)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJ):
	mkdir $(OBJ)

$(NAME): $(LIB) $(OBJS)
	@$(CC) -g -o $(NAME) $(OBJS) $(LIB)

$(LIB):
	@make -C ./libft/
	mv ./libft/$(LIB) ./$(LIB)
	cp ./libft/libft.h ./libft.h

clean:
	$(RM) $(OBJ)/*

fclean: clean
	$(RM) $(NAME) $(LIB)
	make -C libft fclean

re: fclean all

bonus: all

norm:
	@norminette $(SRC)/*.c $(INCLUDES)
	@make norm -C ./libft/

memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pipex infile "wq -l" "ls -a" new

testbonus: all
	./pipex infile "grep his" "sort" "wc -l" o
	< infile grep his | sort | wc -l > o2

test: all
	./pipex infile "grep a" "sort" o
	< infile grep a | sort > o2
	
.PHONY: all clean fclean re norm memcheck bonus
