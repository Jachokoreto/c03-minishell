/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:41 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/23 11:16:56 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{	
	char	*line;

	(void)argv;
	argc = 1;
	data = init_mini(envp);
	shellsignals();
	get_env_array();
	while (1)
	{
		line = readline("Minishell > ");
		if (line == NULL)
			exit(10);
		if (line && *line)
		{
			add_history(line);
			read_commands(data, line);
		}
	}
}
