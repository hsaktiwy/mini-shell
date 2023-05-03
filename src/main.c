/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/01 16:47:48 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		input = readline("username@hostname:[path/current/directory]$ ");
		if (input &&  input[0])
		{
			executer(input);
			add_history(input);
		}
		
		free(input);
	}
	return (0);
} 