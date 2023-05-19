/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/19 10:26:11 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	g_exit_status;
// t_ast	*search(t_ast *ast)
// {
// 	t_ast *tmp;

// 	tmp = ast;
// 	if (tmp)
// 	{
// 		return (tmp->left->left);
// 	}else
// 	{
// 		printf("NULL");
// 	}
// 	return (NULL);
// }

void	set_signal_handlers()
{
	// rl_catch_signals();	//hide printing ^'\'
	// signal(SIGINT, sig_int_handler);	// handel Ctr+c
	signal(SIGQUIT, SIG_IGN);	// ignore Ctr+'\'
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
		printf("\33[3mSHLVL:(%s) exit:(%d):~%s\33[3m", ft_getenv(env_s, "SHLVL"), g_exit_status, getcwd(NULL, 0));
		input = readline("\33[31m<minishell:$>\33[35m ");
		// if the user pressed Ctr+D
		if (!input)
		{
			// ft_free_env(&env_s);
			write(1, "\n", 1);
			exit(0);
		}
		////////////////////////////
		if (input && input[0])
		{
			input = expand_input(env_s, input);
			executer(input, env_s);
			add_history(input);
		}
		free(input);
	}
	return (0);
} 
