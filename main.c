/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:41 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/29 21:25:11 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_launch_minishell(char *line, t_data *data)
{
	mini_lexer(line, data);
	mini_yacc(data);
	executor(data->cmd_grps, data);
	ft_lstclear(&data->tokens, free_token);
	ft_lstclear(&data->cmd_grps, free_cmd_grp);
	unlink("heredocfile");
	exit(g_exit);
}

static void	reset_data(t_data *data)
{
	ft_lstclear(&data->tokens, free_token);
	ft_lstclear(&data->cmd_grps, free_cmd_grp);
	unlink("heredocfile");
}

void	print_welcome(void)
{
	int		fd;
	char	buffer[1];

	fd = open("./banner.txt", O_RDONLY);
	while (read(fd, buffer, 1))
		write(1, buffer, 1);
}

static char	*manage_readline(char *prompt, t_data *data)
{
	char	*line;
	int		i;

	line = readline(prompt);
	if (line == NULL)
	{
		ft_free_all(data);
		system("leaks minishell");
		exit(10);
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ')
		{
			add_history(line);
			return (line);
		}
	}
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data		*data;

	(void)argc;
	(void)argv;
	data = init_mini(envp);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
		ft_launch_minishell(argv[2], data);
	shellsignals();
	print_welcome();
	while (1)
	{
		line = manage_readline("\033[035mminishell🔪\033[0m ", data);
		if (mini_lexer(line, data) == 0)
		{
			mini_yacc(data);
			executor(data->cmd_grps, data);
		}
		reset_data(data);
		free(line);
	}
}
