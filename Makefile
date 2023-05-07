# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 17:53:55 by hsaktiwy          #+#    #+#              #
#    Updated: 2023/05/07 16:18:03 by aigounad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g
SRC = lexer.c parser_tools.c parser.c executer.c main.c free_token.c ast_tools.c lexer_tools.c redirection.c redirection_tools.c expanding_issue.c builtins/cd.c 
BUILTINS = echo.c cd.c
INC = ft_lstdelete_index.c ft_lstadd_in_index.c ft_lstadd_front.c get_next_line_utils.c ft_strcmp.c get_next_line.c ft_realloc.c ft_lstadd_back.c ft_lstnew.c ft_memset.c ft_split.c ft_strlen.c  ft_get_cmd.c ft_lstclear.c ft_lstsize.c ft_next_arg.c ft_strdup.c ft_substr.c ft_get_double_quote.c ft_get_simple_arg.c ft_get_single_quote.c ft_isalnum.c  ft_isalpha.c  ft_isdigit.c  ft_isprint.c  ft_iswhitespace.c ft_strjoin.c  ft_strncat.c
EXP = excep1.c
BUILTINS_HEADER = builtins.h
OBJ = $(SRC:%.c=obj/%.o) $(INC:%.c=obj/include/%.o) $(EXP:%.c=obj/include/exception/%.o)
LIB = src/mini_shell.h
NAME = mini_shell
LIB_INC = include.h
LIB_EXP = exception.h
all : $(NAME)

$(NAME) : $(OBJ) 
	$(CC) $(OBJ) -o $@ -lreadline 
obj/%.o : src/%.c $(LIB)
	$(CC) $(FLAGS) -o $@ -c $< 
obj/include/%.o : include/%.c include/$(LIB_INC)
	$(CC) $(FLAGS) -o $@ -c $<
obj/include/exception/%.o : include/exception/%.c include/$(LIB_EXP)
	$(CC) $(FLAGS) -o $@ -c $<
obj/builtins/%.o : src/builtins/%.c  src/builtins/$(BUILTINS_HEADER)
	$(CC) $(FLAGS) -o $@ -c $<
clean : 
	rm -rf $(OBJ);
fclean : clean
	rm -rf $(NAME);
re :  fclean all

.PHONY: re all clean fclean