/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:41 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/29 18:40:01 by jatan            ###   ########.fr       */
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

	// if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	// {
	// 	exit_status = ft_launch_minishell(argv[2], data);
	// 	exit(exit_status);
	// }

static void	reset_data(t_data *data)
{
	ft_lstclear(&data->tokens, free_token);
	ft_lstclear(&data->cmd_grps, free_cmd_grp);
	unlink("heredocfile");
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
	while (1)
	{
		line = readline("\033[035mminishell🔪\033[0m ");
		if (line == NULL)
		{
			ft_free_all(data);
			// system("leaks minishell");
			exit(10);
		}
		add_history(line);
		if (mini_lexer(line, data) == 0)
		{
			mini_yacc(data);
			executor(data->cmd_grps, data);
		}
		reset_data(data);
		free(line);
	}
}
