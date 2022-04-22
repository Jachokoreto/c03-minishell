/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:41 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/21 14:20:58 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_launch_minishell(char *line, t_data *g_data)
{
	mini_lexer(line, g_data);
	mini_yacc(g_data);
	executor(g_data->cmd_grps, g_data);
	ft_lstclear(&g_data->tokens, free_token);
	ft_lstclear(&g_data->cmd_grps, free_cmd_grp);
	unlink("heredocfile");
	return (0);
}

	// if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	// {
	// 	exit_status = ft_launch_minishell(argv[2], g_data);
	// 	exit(exit_status);
	// }

void	reset_data(t_data *g_data)
{
	ft_lstclear(&g_data->tokens, free_token);
	ft_lstclear(&g_data->cmd_grps, free_cmd_grp);
	unlink("heredocfile");
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data		*g_data;

	(void)argc;
	(void)argv;
	g_data = init_mini(envp);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		int exit_status = ft_launch_minishell(argv[2], g_data);
		exit(exit_status);
	}
	shellsignals();
	while (1)
	{
		line = readline("minishell > ");
		if (line == NULL)
		{
			// maybe no need
			ft_free_all(g_data);
			// system("leaks minishell");
			exit(10);
		}
		if (line && *line)
		{
			add_history(line);
			mini_lexer(line, g_data);
			mini_yacc(g_data);
			executor(g_data->cmd_grps, g_data);
			reset_data(g_data);
			free(line);
		}
	}
}
