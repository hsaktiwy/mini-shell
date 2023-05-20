# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 17:53:55 by hsaktiwy          #+#    #+#              #
#    Updated: 2023/05/20 14:19:32 by aigounad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g -I/goinfre/aigounad/.brew/opt/readline #-fsanitize=address

ENV =  ft_getenv.c ft_setenv.c ft_init_env.c ft_unset_envs.c ft_free_env.c
LIBFT = ft_t_strdup.c ft_iswhitespace.c ft_strjoin.c  ft_strncat.c ft_isalnum.c  ft_isalpha.c  ft_isdigit.c  ft_isprint.c \
		ft_strdup.c ft_substr.c ft_lstclear.c ft_lstsize.c ft_lstdelete_index.c ft_lstadd_in_index.c ft_lstadd_front.c  ft_strcmp.c  \
		ft_realloc.c ft_lstadd_back.c ft_lstnew.c ft_memset.c ft_split.c ft_strlen.c get_next_line.c ft_strchr.c str_join.c ft_atoi.c \
		ft_strtrim.c ft_itoa.c ft_putnbr_fd.c ft_putstr_fd.c ft_putchar_fd.c
SRC = expand.c lexer.c parser_tools.c parser.c executer.c main.c free_token.c ast_tools.c lexer_tools.c redirection.c \
		redirection_tools.c expanding_issue.c execute.c
BUILTINS = cd.c pwd.c echo.c export.c env.c unset.c exit.c common.c
INC = ft_get_cmd.c ft_next_arg.c ft_get_double_quote.c ft_get_simple_arg.c ft_get_single_quote.c ft_lstfree_t_file.c
EXP = excep1.c
OBJ = $(SRC:%.c=obj/%.o) $(BUILTINS:%.c=obj/builtins/%.o) $(ENV:%.c=obj/include/environement/%.o) $(INC:%.c=obj/include/%.o) $(EXP:%.c=obj/include/exception/%.o) $(LIBFT:%.c=obj/include/libft/%.o)
HEADER = src/mini_shell.h
NAME = mini_shell
HEAD_INC = include.h
HEAD_EXP = exception.h
HEAD_GET_N = get_next_line.h
HEAD_LIB = builtins.h
HEAD_ENV = environement.h
all : $(NAME)

$(NAME) : $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) -o $@ -lreadline  -L /goinfre/aigounad/.brew/opt/readline/lib

obj/%.o : src/%.c $(HEADER) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<
obj/include/%.o : include/%.c include/$(HEAD_INC) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<
obj/include/libft/%.o : include/libft/%.c include/libft/$(HEAD_LIB) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<

obj/include/exception/%.o : include/exception/%.c include/$(HEAD_EXP) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<
obj/builtins/%.o : src/builtins/%.c  src/builtins/$(BUILTINS_HEADER) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<
obj/include/environement/%.o : include/environement/%.c  include/environement/$(HEAD_ENV) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<

obj_dir : obj obj/include obj/include/libft obj/include/exception obj/builtins obj/include/environement

obj :
	mkdir obj
obj/include :
	mkdir obj/include
obj/include/libft :
	mkdir obj/include/libft
obj/include/exception :
	mkdir obj/include/exception
obj/builtins :
	mkdir obj/builtins
obj/include/environement :
	mkdir obj/include/environement

clean : 
	rm -rf obj
fclean : clean
	rm -rf $(NAME)
re :  fclean all

.PHONY: re all clean fclean