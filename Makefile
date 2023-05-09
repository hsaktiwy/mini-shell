# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 17:53:55 by hsaktiwy          #+#    #+#              #
#    Updated: 2023/05/09 11:41:11 by aigounad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g
GET_NEXT_LINE = get_next_line_utils.c get_next_line.c 
LIBFT = ft_iswhitespace.c ft_strjoin.c  ft_strncat.c ft_isalnum.c  ft_isalpha.c  ft_isdigit.c  ft_isprint.c ft_strdup.c \
		ft_substr.c ft_lstclear.c ft_lstsize.c ft_lstdelete_index.c ft_lstadd_in_index.c ft_lstadd_front.c  ft_strcmp.c \
		ft_realloc.c ft_lstadd_back.c ft_lstnew.c ft_memset.c ft_split.c ft_strlen.c
SRC = lexer.c parser_tools.c parser.c executer.c main.c free_token.c ast_tools.c lexer_tools.c redirection.c \
		redirection_tools.c expanding_issue.c builtins/cd.c execute.c
BUILTINS = echo.c cd.c
INC = ft_get_cmd.c ft_next_arg.c ft_get_double_quote.c ft_get_simple_arg.c ft_get_single_quote.c ft_lstfree_t_file.c
EXP = excep1.c
OBJ = $(SRC:%.c=obj/%.o) $(INC:%.c=obj/include/%.o) $(EXP:%.c=obj/include/exception/%.o) $(GET_NEXT_LINE:%.c=obj/include/get_next_line/%.o) $(LIBFT:%.c=obj/include/libft/%.o)
HEADER = src/mini_shell.h
NAME = mini_shell
HEAD_INC = include.h
HEAD_EXP = exception.h
HEAD_GET_N = get_next_line.h
HEAD_LIB = builtins.h
all : $(NAME)

$(NAME) : $(OBJ) 
	$(CC) $(OBJ) -o $@ -lreadline 
obj/%.o : src/%.c $(HEADER)
	$(CC) $(FLAGS) -o $@ -c $< 
obj/include/%.o : include/%.c include/$(HEAD_INC)
	$(CC) $(FLAGS) -o $@ -c $<
obj/include/libft/%.o : include/libft/%.c include/libft/$(HEAD_LIB)
	$(CC) $(FLAGS) -o $@ -c $<
obj/include/get_next_line/%.o : include/get_next_line/%.c include/get_next_line/$(HEAD_GET_N)
	$(CC) $(FLAGS) -o $@ -c $<
obj/include/exception/%.o : include/exception/%.c include/$(HEAD_EXP)
	$(CC) $(FLAGS) -o $@ -c $<
obj/builtins/%.o : src/builtins/%.c  src/builtins/$(BUILTINS_HEADER)
	$(CC) $(FLAGS) -o $@ -c $<
clean : 
	rm -rf $(OBJ) obj/include/libft/*.o obj/include/*.o
fclean : clean
	rm -rf $(NAME)
re :  fclean all

.PHONY: re all clean fclean