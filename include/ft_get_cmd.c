/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:07:28 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/03/18 19:34:57 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_cmd	*get_cmd(char *input, int *index)
{
	int		i;
	t_cmd	*cmd;
	int		stack;

	i = 0;
	if (!input)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->arg = NULL;
	if(check_quotes_validity(input))
	{
		// cmd
		
		stack = *index;
		if (input[i] && input[i] != '|')
			cmd->cmd = get_simple_arg(input, index);
		i = (*index) - stack;
		// argument
		while(input[i] && input[i] != '|' && input[i] != '<' && input[i] != '>')
		{
			// printf("i = %d (%s)\n",i, &input[i]);
			ft_lstadd_back(&(cmd->arg), ft_lstnew(get_simple_arg(&input[i], index)));
			i = (*index) - stack;
		}
	}
	return (cmd);	
}

// void	leaks_func()
// {
// 	system("leaks a.out");
// }

// int main(int argc, char **argv)
// {
// 	t_cmd *file;
// 	int index;
// 	atexit(leaks_func);
// 	index = 0;
// 	file = get_cmd("\"$HOME\" $PATH asjkhgjkashdjk \n fgddgjdgh | skhkash", &index);
// 	if (file)
// 	{
// 		printf("%s_%d\n",file->cmd, index);
// 		t_list *lst = file->arg;
// 		int i = 0;
// 		while (lst)
// 		{
// 			printf("%s_%d\n",(char *)lst->content, i);
// 			lst = lst->next;
// 			i++;
// 		}
// 	}
// 	else
// 		printf("(NULL)\n");
// 	if	(file)
// 	{
// 		free(file->cmd);
// 		ft_lstclear(&(file->arg), free);
// 	}
// 		free(file);
// 	return (0);
// }