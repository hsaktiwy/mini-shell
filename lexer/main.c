/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/24 17:49:35 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	signal_handler(int sig)
{
	int fd;

	if (sig == SIGINT)
	{
		if (g_heredoc_executing(-1))
		{
			printf("^C");
			fd = dup(STDIN_FILENO);
			close(STDIN_FILENO);
			g_stdin_fd(fd);
		}
		else if (g_cmd_executing(-1) == 0)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	set_signal_handlers()
{
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);	// handle Ctr+c
	signal(SIGQUIT, signal_handler);	// ignore Ctr+'\'
	signal(SIGTSTP, SIG_IGN);	// ignore Ctr+'z'
}

void	restore_stdin()
{
	if (!isatty(STDIN_FILENO))
	{
		printf("INN\n");
		if (dup2(g_stdin_fd(-1), STDIN_FILENO) == -1)
			perror("dup2");
		if (close(g_stdin_fd(-1)) == -1)
			perror("close");
	}
	g_stdin_fd(-2);
}

void	main2(char *input, t_env *env)
{
	t_list	*tokens;
	int		err_lex;
	t_list	*list;
	
	tokens = NULL;
	err_lex = lexical_erreur(input);
	g_pipe_count(0);
	if (err_lex != -1)
		lexer_err(&input[err_lex]);
	else
		lexer(&tokens, input, env);
	if (err_lex == -1)
	{
		// display_tokens(tokens);
		fix_expanding_issue(&tokens);
		ini_arg_count(&tokens);
		list = parser(env, &tokens, input);
		g_token_l(tokens);
		// display_tokens(tokens);
		// display_tokens(list);
		if(list)
			execute(list);
		unlink(".here_doc");
	}
	free_tokens(&tokens);
}

int	main(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av, char **env)
{
	char	*input;
	t_env	*env_s;

	set_signal_handlers();
	env_s = ft_init_env(env);
	while (1)
	{
		restore_stdin();
		// char buf[4000];
		// getcwd(buf, 4000);
		// printf("\33[31mSHLVL:(%s) exit:(%d):~%s#\33[00m", ft_getenv(env_s, "SHLVL"), g_exit_status, buf);
		input = readline("\33[31mminishell:$>\33[35m ");
		// input = "exit";
		// if the user pressed Ctr+D
		if (!input)
		{
			ft_free_env(&env_s);
			write(1, "exit\n", 5);
			exit(0);
		}
		////////////////////////////
		if (input && input[0])
		{
			add_history(input);
			input = expand_input(env_s, input);
			main2(input, env_s);
		}
		// system("leaks mini_shell");
		free(input);
		// break;
	}
	return (0);
}
