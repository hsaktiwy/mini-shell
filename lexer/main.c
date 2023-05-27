/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/27 21:34:29 by aigounad         ###   ########.fr       */
=======
/*   Updated: 2023/05/27 20:25:10 by hsaktiwy         ###   ########.fr       */
>>>>>>> hsaktiwy
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

// void	unlink_here_doc()
// {
// 	int		size;
// 	int		i;
// 	char	*name;

// 	i = 0;
// 	size = g_heredoc_count(-1);
// 	while (i < size)
// 	{
// 		name = here_doc_name(".here_doc", ++i);
// 		unlink(name);
// 		free(name);
// 	}
// 	g_heredoc_count(0);
// }

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
			g_cmd_executing(-2);
			g_stdin_fd(fd);
		}
		else if (g_cmd_executing(-1) == 0)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_exit_status = 1;
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
	if (!isatty(STDIN_FILENO) && g_stdin_fd(-1) != 0)
	{
		if (dup2(g_stdin_fd(-1), STDIN_FILENO) == -1)
			perror("minishell: dup2");
		if (close(g_stdin_fd(-1)) == -1)
			perror("minishell: close");
	}
	g_stdin_fd(0);
}

void	main2(char *input, t_env *env)
{
	t_list	*tokens;
	int		err_lex;
	t_list	*list;
	
	tokens = NULL;
	err_lex = lexical_erreur(input);
	g_pipe_count(0);
	g_heredoc_count(0);
	if (err_lex != -1)
		lexer_err(&input[err_lex]);
	else
		lexer(&tokens, input, env);
	if (err_lex == -1)
	{
		//display_tokens(tokens);
		fix_expanding_issue(&tokens);
		ini_arg_count(&tokens);
		//display_tokens(tokens);
		list = parser(env, &tokens, input);
		g_token_l(tokens);
		//display_tokens(tokens);
		// display_tokens(list);
		if(list)
			execute(list);
		ft_lstclear(&list, NULL);
	}
	free_tokens(&tokens);
}

// void ft_leaks()
// {
// 	system("leaks minishell");
// }
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
		input = readline("minibash-3.2$ ");
		// input = "exit";
		// if the user pressed Ctr+D
		if (!input)
		{
			ft_free_env(&env_s);
			write(1, "exit\n", 5);
			exit(g_exit_status);
		}
		if (input && input[0])
		{
			add_history(input);
			input = expand_input(env_s, input);
			main2(input, env_s);
		}
		free(input);
	}
	return (0);
}
