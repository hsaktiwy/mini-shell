/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/09 22:22:13 by aigounad         ###   ########.fr       */
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

	char path[4096];

	env_s = ft_init_env(env);
	while (1)
	{
		getcwd(path, 4096);
		printf("[%s]", path);
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