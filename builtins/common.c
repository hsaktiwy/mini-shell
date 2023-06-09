/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:45:11 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/08 17:27:59 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(char *key)
{
	size_t	i;

	if (!key)
		return (1);
	if (key
		&& !((key[0] >= 'a' && key[0] <= 'z')
			|| (key[0] >= 'A' && key[0] <= 'Z'))
		&& (key[0] != '_'))
		return (1);
	i = 1;
	while (key[i])
	{
		if ((key[i] >= 'a' && key[i] <= 'z')
			|| (key[i] >= 'A' && key[i] <= 'Z')
			|| (key[i] >= '0' && key[i] <= '9')
			|| key[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

int	print_error2(char *identifier, int i)
{
	if (i == 1)
		write(STDERR_FILENO, "minishell: export: `", 20);
	if (i == 2)
		write(STDERR_FILENO, "minishell: unset: `", 19);
	write(STDERR_FILENO, identifier, ft_strlen(identifier));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	return (1);
}

int	f(char *key1, char*key2)
{
	if (ft_strcmp(key1, key2) <= 0)
		return (0);
	else
		return (1);
}

void	ft_void(void)
{
	return ;
}

void	sort_env_list(t_list *head)
{
	char	*p;
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		while (tmp)
		{
			if (f(((t_holder *)(head->content))->key,
				((t_holder *)(tmp->content))->key))
			{
				p = ((t_holder *)(head->content))->key;
				((t_holder *)(head->content))->key = \
				((t_holder *)(tmp->content))->key;
				((t_holder *)(tmp->content))->key = p;
				p = ((t_holder *)(head->content))->value;
				((t_holder *)(head->content))->value = \
				((t_holder *)(tmp->content))->value;
				((t_holder *)(tmp->content))->value = p;
			}
			tmp = tmp->next;
		}
		head = head->next;
	}
}
