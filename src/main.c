/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/20 11:45:58 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	g_exit_status;

void	sig_int_handler(int sig)
{
	if (sig == SIGINT)
	{
		t_env *env = global_env(NULL);
		ft_free_env(&env);
		exit(0);
		write(1, "\n", 1);
	}
}

void	set_signal_handlers()
{
	// rl_catch_signals();	//hide printing ^'\'
	signal(SIGINT, sig_int_handler);	// handel Ctr+c
	signal(SIGQUIT, SIG_IGN);	// ignore Ctr+'\'
	signal(SIGTSTP, SIG_IGN);	// ignore Ctr+'z'
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
		// printf("\33[3mSHLVL:(%s) exit:(%d):~%s\33[3m", ft_getenv(env_s, "SHLVL"), g_exit_status, getcwd(NULL, 0));
		// input = readline("\33[31m<minishell:$>\33[35m ");
		input = "unset HOME | ls";
		// if the user pressed Ctr+D
		if (!input)
		{
			ft_free_env(&env_s);
			write(1, "\n", 1);
			exit(0);
		}
		// if (strcmp(input, "^C") == 0 || strcmp(input, "SIGINT") == 0) {
		// 	// Perform the action for canceling or interrupting the current operation.
		// 	// For example, clear the input line and display a new prompt.
		// 	rl_on_new_line();
		// 	// rl_replace_line("", 0);
		// 	rl_redisplay();
		// }
		////////////////////////////
		if (input && input[0])
		{
			// add_history(input);
			input = expand_input(env_s, input);
			executer(input, env_s);
		}
		free(input);
		break ;
	}
	return (0);
}
