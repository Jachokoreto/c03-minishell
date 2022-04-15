/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:41 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/15 11:34:38 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{	
	char		*line;
	t_cmd_grp	*cmd_grp;

	(void)argv;
	argc = 1;
	g_data = init_mini(envp);
	shellsignals();
	// get_env_array(); // do we even need this?
	//heredoc("hello");
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
			// system("leaks minishell");
			exit(10);
		}
		if (line && *line)
		{
			add_history(line);
			parser(line);
			cmd_grp = g_data->cmd_grps->content;
			// printf("%s\n", cmd_grp->args[0]);
			g_data->pipe_number = ft_lstsize(g_data->cmd_grps) - 1;
			read_commands(g_data->cmd_grps);
			ft_lstclear(&g_data->tokens, free_token);
			ft_lstclear(&g_data->cmd_grps, free_cmd_grp);
			unlink("heredocfile");
		}
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
  	{
    int exit_status = ft_launch_minishell(argv[2]);
    exit(exit_status);
  	}
	}
}
