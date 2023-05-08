/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/07 19:00:12 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_ast	*search(t_ast *ast)
{
	t_ast *tmp;

	tmp = ast;
	if (tmp)
	{
		return (tmp->left->left);
	}else
	{
		printf("NULL");
	}
	return (NULL);
}
int	main(int argc, char **argv, char **env)
{
	char	*input;
	(void)argc;
	(void)argv;
	(void)env;
	t_env	*env_s;

	env_s = ft_init_env(env);
	while (1)
	{
		input = readline("\33[31mminishell:$>\33[35m ");
		if (input &&  input[0])
		{
			executer(input, env_s);
			add_history(input);
		}
		free(input);
	}
	return (0);
} 