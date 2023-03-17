# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 17:53:55 by hsaktiwy          #+#    #+#              #
#    Updated: 2023/03/16 10:35:44 by hsaktiwy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror
SRC = lexer.c parser.c executer.c main.c
INC = ft_lstadd_back.c ft_lstnew.c ft_memset.c ft_split.c ft_strlen.c  ft_get_cmd.c ft_lstclear.c ft_lstsize.c ft_next_arg.c ft_strdup.c ft_substr.c
EXP = excep1.c
OBJ = $(SRC:%.c=obj/%.o) $(INC:%.c=obj/include/%.o) $(EXP:%.c=obj/include/exception/%.o)
LIB = src/mini_shell.h
NAME = mini_shell
LIB_INC = include.h
LIB_EXP = exception.h
all : $(NAME)

$(NAME) : $(OBJ) 
	$(CC) $(FLAGS)  $(OBJ) -o $@ -lreadline
obj/%.o : src/%.c $(LIB)
	$(CC) $(FLAGS) -o $@ -c $<
obj/include/%.o : include/%.c $(LIB_INC)
	$(CC) $(FLAGS) -o $@ -c $<
obj/include/exception/%.o : include/exception/%.c $(LIB_EXP)
	$(CC) $(FLAGS) -o $@ -c $<
clean : 
	rm -rf $(OBJ);
fclean : clean
	rm -rf $(NAME);
re :  fclean all

.PHONY: re all clean fclean