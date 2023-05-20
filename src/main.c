/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/20 14:37:09 by hsaktiwy         ###   ########.fr       */
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

// char *getcwd(char *buf, size_t size); allocate memory to be free
		/* If buf is NULL, space is allocated as necessary to store the pathname and
     size is ignored.  This space may later be free(3)'d. (there is a leaks here )*/
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
		// printf("\33[31mSHLVL:(%s) exit:(%d):~%s\33[00m", ft_getenv(env_s, "SHLVL"), g_exit_status, getcwd(NULL, 0));
		input = readline("\33[31mminishell:$>\33[35m ");
		// input = "ls | wc";
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
			add_history(input);
			input = expand_input(env_s, input);
			executer(input, env_s);
		}
		//system("leaks mini_shell");
		free(input);
	}
	return (0);
}
