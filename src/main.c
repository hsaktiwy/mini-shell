/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/07 16:28:08 by aigounad         ###   ########.fr       */
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
	t_ast	*ast;
	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		input = readline("username@hostname:[path/current/directory]$ ");
		if (input &&  input[0])
		{
			
			ast = executer(input);
			display_ast_types(ast, "root");
			printf("\n");
			t_ast *node = search(ast);
			if (node != NULL)
			{
				t_cmd *cmd;
				printf("node type = %d\n", node->type);
				cmd =((t_cmd *)(((t_token *)(node->content))->value));
				printf("not here\n");
				printf("cmd->cmd : %s\n",cmd->cmd);
				if (cmd)
					printf("cdm  = %s\n", cmd->cmd);
				else
					printf("NULL value\n");
				cd(cmd,env);
			}
			add_history(input);
		}
		
		free(input);
	}
	return (0);
} 