/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/05 22:26:29 by aigounad         ###   ########.fr       */
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
	char	*data;

	data = ft_strtrim(input, " ");
	tokens = NULL;
	//printf("hello\n");
	err_lex = lexical_erreur(data);
	g_pipe_count(0);
	g_heredoc_count(0);
	if (err_lex != -1)
		lexer_err(&data[err_lex]);
	else
		lexer(&tokens, data, env);
	//printf("lexer_step done\n");
	if (err_lex == -1)
	{
		//fix_expanding_issue(&tokens);
		ini_arg_count(&tokens);
		list = parser(env, &tokens, data);
		display_tokens(tokens);
		g_token_l(tokens);
		if (list)
			execute(list);
		ft_lstclear(&list, NULL);
	}
	free_tokens(&tokens);
	free(data);
}

void ft_leaks()
{
	system("leaks minishell");
}
int	next_is_not(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (iswhitespace(str[i]))
			i++;
		else if (str[i] == c)
			return (0);
		else
			break ;
	}
	return (1);
}

int	check_redirection(char *input)
{
	int		i;
	char	*res;
	t_env	*env;
	int		count;

	res = input;
	i = -1;
	count = 0;
	while (res[++i])
	{
		if (res[i] == '<' && res[i + 1] && res[i + 1] == '<')
		{
			count++;
			i++;
		}
		else if (res[i] == '|')
		{
			if (i == 0)
				break ;
			else if (!next_is_not(&res[i + 1], '|'))
				break ;
			else if (!res[i + 1])
				break ;
		}
	}
	if (count > 16)
	{
		ft_putstr_fd("minibash: maximum here-document count exceeded\n",
			STDERR_FILENO);
		env = g_env_s(NULL);
		ft_free_env(&env);
		free(input);
		exit(2);
	}
	return (1);
}

int	main(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av, char **env)
{
	char	*input;
	t_env	*env_s;

	//atexit(ft_leaks);
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
			//input = expand_input(env_s, input);
			//printf("our input : %s\n", input);
			g_input_line(input);
			if(check_redirection(input))
				main2(input, env_s);
		}
		free(input);
	}
	return (0);
}
