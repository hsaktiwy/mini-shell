# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 13:01:11 by hsaktiwy          #+#    #+#              #
#    Updated: 2023/06/08 17:04:16 by aigounad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FSAN = -fsanitize=address
# FLAGS = -Wall -Wextra -Werror -g -I/Users/hsaktiwy/.brew/opt/readline/include -I$(INCLUDE_DIR) $(FSAN)
FLAGS = -Wall -Wextra -Werror -g -I/Users/aigounad/.brew/opt/readline/include -I$(INCLUDE_DIR) $(FSAN)

ENV =  ft_getenv.c ft_setenv.c ft_setenv_utils.c ft_init_env.c ft_init_env_utils.c ft_unset_envs.c ft_free_env.c

LIBFT = ft_t_strdup.c ft_iswhitespace.c ft_strjoin.c  ft_strncat.c ft_isalnum.c  ft_isalpha.c  ft_isdigit.c  ft_isprint.c \
		ft_strdup.c ft_substr.c ft_lstclear.c ft_lstsize.c ft_lstdelete_index.c ft_lstadd_in_index.c ft_lstadd_front.c  ft_strcmp.c  \
		ft_realloc.c ft_lstadd_back.c ft_lstnew.c ft_memset.c ft_split.c ft_strlen.c get_next_line.c ft_strchr.c str_join.c ft_atoi.c \
		ft_strtrim.c ft_itoa.c ft_putnbr_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_strncmp.c str_len.c ft_replace.c ft_strstr.c

PARSER = parser.c parser_tools.c redirection.c redirection_tools.c redirection_s_tools.c redirection_t_tools.c

BUILTINS = cd.c pwd.c echo.c export.c env.c unset.c exit.c common.c

LEXER = main.c ft_get_cmd.c ft_next_arg.c expand_var.c expand_var_tools.c ft_lstfree_t_file.c display_tokens.c \
		expand.c lexer.c lexer_tools.c expanding_issue.c free_token.c global_functions.c wildcards.c lexer_utils.c \
		lexer_second_utils.c wildcards_utils.c wildcards_second_utils.c global_functions_second.c expand_input.c lexer_tools_second.c \
		expand_input_tools.c tools.c

EXEC = execute.c execute_utils.c execute_utils_2.c find_cmd.c signals.c builtin_execution.c

OBJ = $(LEXER:%.c=obj/lexer/%.o) $(BUILTINS:%.c=obj/builtins/%.o) $(ENV:%.c=obj/environment/%.o)  \
		$(LIBFT:%.c=obj/libft/%.o) $(PARSER:%.c=obj/parser/%.o) $(EXEC:%.c=obj/execution/%.o)
HEADER = include/minishell.h include/structers.h
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
	@$(CC) $(FLAGS) $(OBJ) -o $@ -lreadline  -L /Users/hsaktiwy/.brew/opt/readline/lib -L /Users/aigounad/.brew/opt/readline/lib
	@echo "Compilation completed."

obj/parser/%.o : parser/%.c $(HEAD_PAR) | obj_dir
	@echo "Compiling" $<
	@$(CC) $(FLAGS) -o $@ -c $<
obj/lexer/%.o : lexer/%.c $(HEAD_LEX) | obj_dir
	@echo "Compiling" $<
	@$(CC) $(FLAGS) -o $@ -c $<
obj/libft/%.o : libft/%.c $(HEAD_LIB) | obj_dir
	@echo "Compiling" $<
	@$(CC) $(FLAGS) -o $@ -c $<
obj/execution/%.o : execution/%.c $(HEAD_EXE) | obj_dir
	@echo "Compiling" $<
	@$(CC) $(FLAGS) -o $@ -c $<
obj/builtins/%.o : builtins/%.c $(HEAD_BUI) | obj_dir
	@echo "Compiling" $<
	@$(CC) $(FLAGS) -o $@ -c $<
obj/environment/%.o : environment/%.c $(HEAD_ENV) | obj_dir
	@echo "Compiling" $<
	@$(CC) $(FLAGS) -o $@ -c $<

obj_dir : obj obj/lexer obj/parser obj/libft obj/builtins obj/environment obj/execution

obj :
	@mkdir obj
obj/lexer :
	@mkdir obj/lexer
obj/parser :
	@mkdir obj/parser
obj/libft :
	@mkdir obj/libft
obj/builtins :
	@mkdir obj/builtins
obj/environment :
	@mkdir obj/environment
obj/execution :
	@mkdir obj/execution

clean :
	@echo "Cleaning up..."
	@rm -rf obj
	@echo "Cleanup completed."
fclean : clean
	@rm -rf $(NAME)
re :  fclean all

.PHONY: all clean fclean obj_dir re
