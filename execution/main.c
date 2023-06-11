/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:53 by hsaktiwy          #+#    #+#             */
/*   Updated: 2023/06/11 20:31:44 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main2(char *data, t_env *env)
{
	t_list	*tokens;
	int		err_lex;
	t_list	*list;

	tokens = NULL;
	err_lex = parser_erreur(data);
	g_heredoc_count(0);
	if (err_lex != -1)
		lexer_err(&data[err_lex]);
	else
		lexer(&tokens, data, env);
	if (err_lex == -1)
	{
		g_token_l(tokens);
		ini_arg_count(&tokens);
		list = parser(&tokens, data);
		if (list)
			execute(list);
		ft_lstclear(&list, NULL);
	}
	free_tokens(&tokens);
}

int	main(__attribute__((unused)) int ac, __attribute__((unused)) char **av,
		char **env)
{
	char	*input;
	t_env	*env_s;

	set_signal_handlers();
	env_s = ft_init_env(env);
	while (1)
	{
		restore_stdin();
		input = get_input();
		if (!input)
		{
			ft_free_env(&env_s);
			if (isatty(STDIN_FILENO))
				write(1, "exit\n", 5);
			exit(g_exit_status);
		}
		if (input && input[0] && input[0] != '#')
		{
			add_history(input);
			if (check_redirection(input))
				main2(input, env_s);
		}
		free(input);
	}
	return (0);
}
