/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/01 00:14:18 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	g_fix_sigint(int i)
{
	static int	var;

	var += i;
	return (var);
}

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
			g_fix_sigint(2);
		}
		else if (g_cmd_executing(-1) == 0)
		{
			if (g_fix_sigint(0) == 0)
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
	// rl_catch_signals = 0;

	signal(SIGINT, signal_handler);	// handle Ctr+c
	signal(SIGQUIT, signal_handler);	// ignore Ctr+'\'
	signal(SIGTSTP, SIG_IGN);	// ignore Ctr+'z'
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
	if (g_fix_sigint(0) > 0)
		g_fix_sigint(-1);
}
#include <sys/time.h>
void	show_time(char *str)
{
	long int time;
	static long int s_ts;
	struct timeval tm;

	if (str == NULL)
	{
		gettimeofday(&tm, NULL);
		s_ts = tm.tv_sec * 1000 + tm.tv_usec / 1000;
	}
	else
	{
		gettimeofday(&tm, NULL);
		time = tm.tv_sec * 1000 + tm.tv_usec / 1000;
		printf("time of %s : %ld(current: %ld, start: %ld)\n", str,time - s_ts, time, s_ts);
	}
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
	// show_time(NULL);
	//show_time("Before lexing");
	//show_time("Before lexing");
	if (err_lex != -1)
		lexer_err(&input[err_lex]);
	else
		lexer(&tokens, input, env);
	//show_time("After lexing");
	if (err_lex == -1)
	{
		//display_tokens(tokens);
		// show_time("Before addition data info");
		fix_expanding_issue(&tokens);
		ini_arg_count(&tokens);
		//show_time("After addition data info");
		//display_tokens(tokens);
		//show_time("Before parser");
		list = parser(env, &tokens, input);
		//show_time("After parser");
		g_token_l(tokens);
		//display_tokens(tokens);
		//display_tokens(list);
		// show_time("Before execution");
		if(list)
			execute(list);
		// show_time("After execution");
		ft_lstclear(&list, NULL);
	}
	free_tokens(&tokens);
}

// void ft_leaks()
// {
// 	system("leaks minishell");
// }
int	check_redirection(char *input)
{
	int		i;
	char	*res;

	res = input;
	i = -1;
	while (res)
	{
		i++;
		res = strstr(res, "<<");
		if (res)
			res = &res[2];
	}
	if (i > 16)
	{
		ft_putstr_fd("minibash: maximum here-document count exceeded\n",
			STDERR_FILENO);
		// free and exit(2)
		return (0);
	}
	return (1);
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
		input = readline("minibash-3.2$ ");
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
			input = iswildcards(input);
			if(check_redirection(input))
				main2(input, env_s);
		}
		free(input);
	}
	return (0);
}
