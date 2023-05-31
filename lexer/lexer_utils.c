/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaktiwy <hsaktiwy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:11:29 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/05/31 14:12:27 by hsaktiwy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_err(char *str)
{
	ft_putstr_fd("\33[33mParse Error near: \33[00m\33[30m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\33[00m\n", 2);
}

char	*here_doc_name(char *common, int nbr)
{
	char	*str;
	char	*integer;

	integer = ft_itoa(nbr);
	str = ft_strjoin(common, integer);
	free(integer);
	return (str);
}

int	get_start(char *str)
{
	int		i;

	i = 0;
	surpace_whitesspaces(str, &i);
	while (str[i] && !iswhitespace(str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}
// this may need to be in int not void cause it can return 
//0 when the allocation fail (this can cause some indefine behavior)

void	add_fake_cmd(t_list **tokens, int cmd)
{
	t_token	*fake_cmd;

	if (cmd == 0)
	{
		fake_cmd = (t_token *)malloc(sizeof(t_token));
		if (!fake_cmd)
			return ;
		fake_cmd->type = COMMAND;
		fake_cmd->value = ini_cmd(g_env_s(NULL));
		ft_lstadd_back(tokens, ft_lstnew(fake_cmd));
	}
}
