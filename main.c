/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:41 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/08 15:23:43 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{	
	char	*line;

	(void)argv;
	argc = 1;
	g_data = init_mini(envp);
	shellsignals();
	get_env_array();
	while (1)
	{
		line = readline("minishell > ");
		// heredoc("hello");
		if (line == NULL)
			exit(10);
		if (line && *line)
		{
			add_history(line);
			parser(line);
			// read_commands(g_data, line);
			ft_lstclear(&g_data->tokens, free);
			ft_lstclear(&g_data->cmd_grps, free);
		}
	}
}
