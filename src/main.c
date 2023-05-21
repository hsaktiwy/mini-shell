/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/21 13:23:23 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	g_exit_status;
int	g_stdin_fd(int i)
{
	static int	j;
	if (i == -1)
		return (j);
	j = i;
	return (j);
}

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

// char *getcwd(char *buf, size_t size); allocate memory to be free
		/* If buf is NULL, space is allocated as necessary to store the pathname and
     size is ignored.  This space may later be free(3)'d. (there is a leaks here )*/
void	set_signal_handlers()
{
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);	// handel Ctr+c
	signal(SIGQUIT, signal_handler);	// ignore Ctr+'\'
	signal(SIGTSTP, SIG_IGN);	// ignore Ctr+'z'
}

void	restore_stdin()
{
	if (!isatty(STDIN_FILENO))
	{
		if (dup2(g_stdin_fd(-1), STDIN_FILENO) == -1)
			perror("dup2");
		if (close(g_stdin_fd(-1)) == -1)
			perror("close");
	}
	g_stdin_fd(-2);
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
		// printf("\33[31mSHLVL:(%s) exit:(%d):~%s\33[00m", ft_getenv(env_s, "SHLVL"), g_exit_status, getcwd(NULL, 0));
		input = readline("\33[31m<minishell:$>\33[35m ");
		// input = "exit | ls";
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
			executer(input, env_s);
		}
		// system("leaks mini_shell");
		free(input);
		// break;
	}
	return (0);
}
