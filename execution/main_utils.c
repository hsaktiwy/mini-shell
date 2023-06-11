/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 00:48:08 by aigounad          #+#    #+#             */
/*   Updated: 2023/06/11 00:59:25 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	char	*s1;
	char	*cwd;
	char	*s2;

	cwd = getcwd(NULL, PATH_MAX + 1);
	s1 = ft_strjoin("(", "minishell");
	s2 = ft_strjoin(s1, ")");
	free(s1);
	s1 = ft_strjoin(s2, "-[");
	free(s2);
	s2 = ft_strjoin(s1, cwd);
	free(s1);
	free(cwd);
	s1 = ft_strjoin(s2, "] ");
	free(s2);
	return (s1);
}

void	signal_handler(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
		if (g_heredoc_executing(-1))
		{
			printf("^C");
			fd = dup(STDIN_FILENO);
			close(STDIN_FILENO);
			g_cmd_executing(-2);
			g_stdin_fd(fd);
		}
		else if (g_cmd_executing(-1) == 0)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_exit_status = 1;
	}
}

void	set_signal_handlers(void)
{
	// rl_catch_signals = 0;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTSTP, SIG_IGN);
}

void	restore_stdin(void)
{
	if (!isatty(STDIN_FILENO) && g_stdin_fd(-1) != 0)
	{
		if (dup2(g_stdin_fd(-1), STDIN_FILENO) == -1)
			perror("minishell: dup2");
		if (close(g_stdin_fd(-1)) == -1)
			perror("minishell: close");
	}
	g_stdin_fd(0);
}
char	*get_input(void)
{
	char	*input;
	char	*line;
	char	*prompt;

	prompt = get_prompt();
	if (isatty(STDIN_FILENO))
		line = readline(prompt);
	else
	{
		g_script_mode(1);
		line = get_next_line(STDIN_FILENO);
	}
	input = ft_strtrim(line, " \t\v\f\r\n");
	free(line);
	free(prompt);
	g_input_line(input);
	return (input);
}
