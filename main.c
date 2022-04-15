/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:41 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/15 15:54:03 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{	
	char		*line;
	t_cmd_grp	*cmd_grp;
	t_data		*g_data;

	(void)argv;
	argc = 1;
	g_data = init_mini(envp);
	shellsignals();
	while (1)
	{
		line = readline("minishell > ");
		if (line == NULL)
		{
			ft_lstclear(&g_data->env_list, free_env);
			ft_lstclear(&g_data->tokens, free_token);
			ft_lstclear(&g_data->cmd_grps, free_cmd_grp);
			free_str_array(g_data->builtins);
			free(g_data);
			exit(10);
		}
		if (line && *line)
		{
			add_history(line);
			mini_lexer(line, g_data);
			mini_yacc(g_data);
			cmd_grp = g_data->cmd_grps->content;
			read_commands(g_data->cmd_grps, g_data,
				ft_lstsize(g_data->cmd_grps) - 1);
			ft_lstclear(&g_data->tokens, free_token);
			ft_lstclear(&g_data->cmd_grps, free_cmd_grp);
			unlink("heredocfile");
		}
	}
}
