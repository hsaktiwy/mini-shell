/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/10 17:10:02 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	set_signal_handlers()
{
	// rl_catch_signals = 0;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTSTP, SIG_IGN);
}

void	restore_stdin(void)
{
	if (!isatty(STDIN_FILENO) && g_stdin_fd(-1) != 0)
	{
		if (dup2(g_stdin_fd(-1), STDIN_FILENO) == -1)
			perror("minishell: dup2");
		if (close(g_stdin_fd(-1)) == -1)
			perror("minishell: close");
	}
	g_stdin_fd(0);
}

char	*get_input(void)
{
	char	*input;
	char	*line;

	if (isatty(STDIN_FILENO))
		input = readline("minibash-3.2$ ");
	else
	{
		g_script_mode(1);
		line = get_next_line(STDIN_FILENO);
		input = ft_strtrim(line, " \t\v\n");
		free(line);
	}
	g_input_line(input);
	return (input);
}

void	main2(char *input, t_env *env)
{
	t_list	*tokens;
	int		err_lex;
	t_list	*list;
	char	*data;

	data = ft_strtrim(input, " \t\v");
	tokens = NULL;
	err_lex = lexical_erreur(data);// parsing Errur
	g_pipe_count(0);// ?
	g_heredoc_count(0);
	if (err_lex != -1)
		lexer_err(&data[err_lex]);
	else
		lexer(&tokens, data, env);
	//printf("lexer_step done\n");
	if (err_lex == -1)
	{
		// display_tokens(tokens);
		//fix_expanding_issue(&tokens);
		ini_arg_count(&tokens);
		g_token_l(tokens);
		list = parser(&tokens, data);
		// display_tokens(tokens);
		if (list)
			execute(list);
		ft_lstclear(&list, NULL);
	}
	free_tokens(&tokens);
	free(data);
}

void	leaks()
{
	system("leaks minishell");
}

int	main(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av, char **env)
{
	char	*input;
	t_env	*env_s;

	// atexit(leaks);
	set_signal_handlers();
	env_s = ft_init_env(env);
	////////////////////////////////////////////
	//this part is for tester
	if (ac == 3)
	{
		if (ft_strcmp(av[1], "-c") == 0)
		{
			input = ft_strdup(av[2]);
			if (!input)
			{
				ft_free_env(&env_s);
				write(1, "exit\n", 5);
				exit(g_exit_status);
			}
			if (input && input[0])
			{
				add_history(input);
				g_input_line(input);
				if(check_redirection(input))
					main2(input, env_s);
			}
			free(input);
		}
		return (g_exit_status);
	}
	//////////////////////////////////////////////
	while (1)
	{
		restore_stdin();
		input = get_input();
		if (!input)
		{
			ft_free_env(&env_s);
			if (isatty(STDIN_FILENO))
				write(1, "exit\n", 5);
			exit(g_exit_status);
		}
		if (input && input[0] && input[0] != '#')
		{
			add_history(input);
			// input = expand_input(env_s, input);
			//printf("our input : %s\n", input);
			if (check_redirection(input))
				main2(input, env_s);
		}
		free(input);
	}
	return (0);
}
