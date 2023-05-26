# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 13:01:11 by hsaktiwy          #+#    #+#              #
#    Updated: 2023/05/26 15:21:24 by hsaktiwy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

FLAGS = -Wall -Wextra -Werror -g -I/Users/hsaktiwy/.brew/opt/readline/include -I$(INCLUDE_DIR) -fsanitize=address
# FLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I/Users/aigounad/.brew/opt/readline/include -I$(INCLUDE_DIR)

ENV =  ft_getenv.c ft_setenv.c ft_setenv_utils.c ft_init_env.c ft_init_env_utils.c ft_unset_envs.c ft_free_env.c

LIBFT = ft_t_strdup.c ft_iswhitespace.c ft_strjoin.c  ft_strncat.c ft_isalnum.c  ft_isalpha.c  ft_isdigit.c  ft_isprint.c \
		ft_strdup.c ft_substr.c ft_lstclear.c ft_lstsize.c ft_lstdelete_index.c ft_lstadd_in_index.c ft_lstadd_front.c  ft_strcmp.c  \
		ft_realloc.c ft_lstadd_back.c ft_lstnew.c ft_memset.c ft_split.c ft_strlen.c get_next_line.c ft_strchr.c str_join.c ft_atoi.c \
		ft_strtrim.c ft_itoa.c ft_putnbr_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_strncmp.c str_len.c

PARSER = parser.c parser_tools.c redirection.c redirection_tools.c

BUILTINS = cd.c pwd.c echo.c export.c env.c unset.c exit.c common.c

LEXER = main.c ft_get_cmd.c ft_next_arg.c ft_get_double_quote.c ft_get_simple_arg.c ft_get_single_quote.c ft_lstfree_t_file.c \
		expand.c lexer.c lexer_tools.c expanding_issue.c free_token.c display_tokens.c global_functions.c

EXEC = execute.c execute_utils.c execute_utils_2.c find_cmd.c signals.c builtin_execution.c

OBJ = $(LEXER:%.c=obj/lexer/%.o) $(BUILTINS:%.c=obj/builtins/%.o) $(ENV:%.c=obj/environment/%.o)  \
		$(LIBFT:%.c=obj/libft/%.o) $(PARSER:%.c=obj/parser/%.o) $(EXEC:%.c=obj/execution/%.o)
HEADER = include/minishell.h
NAME = minishell
INCLUDE_DIR = ./include
HEAD_LEX = include/lexer.h $(HEADER)
HEAD_BUI = include/builtins.h $(HEADER)
HEAD_LIB = include/libft.h $(HEADER)
HEAD_ENV = include/environment.h $(HEADER)
HEAD_PAR = include/parser.h $(HEADER)
HEAD_EXE = include/execution.h $(HEADER)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ -lreadline  -L /Users/hsaktiwy/.brew/opt/readline/lib
#	$(CC) $(FLAGS) $(OBJ) -o $@ -lreadline  -L /Users/aigounad/.brew/opt/readline/lib

obj/parser/%.o : parser/%.c $(HEAD_PAR) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<
obj/lexer/%.o : lexer/%.c $(HEAD_LEX) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<
obj/libft/%.o : libft/%.c $(HEAD_LIB) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<
obj/execution/%.o : execution/%.c $(HEAD_EXE) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<
obj/builtins/%.o : builtins/%.c $(HEAD_BUI) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<
obj/environment/%.o : environment/%.c $(HEAD_ENV) | obj_dir
	$(CC) $(FLAGS) -o $@ -c $<

obj_dir : obj obj/lexer obj/parser obj/libft obj/builtins obj/environment obj/execution

obj :
	mkdir obj
obj/lexer :
	mkdir obj/lexer
obj/parser :
	mkdir obj/parser
obj/libft :
	mkdir obj/libft
obj/builtins :
	mkdir obj/builtins
obj/environment :
	mkdir obj/environment
obj/execution :
	mkdir obj/execution

clean : 
	rm -rf obj
fclean : clean
	rm -rf $(NAME)
re :  fclean all

.PHONY: re all clean fclean
