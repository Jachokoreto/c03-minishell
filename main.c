/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:41 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/30 14:20:44 by jatan            ###   ########.fr       */
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
		if (line == NULL)
			exit(10);
		if (line && *line)
		{
			add_history(line);
			parser(line);
			run_command(g_data, line);
			ft_lstclear(&g_data->tokens, free);
			g_data->tokens = NULL;
		}
	}
}
