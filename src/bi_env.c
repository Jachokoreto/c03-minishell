/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:38 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/05 16:55:04 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(void *content)
{
	t_env	*tmp;

	tmp = (t_env *)content;
	printf("%s=%s\n", tmp->key, tmp->value);
}

int	env(char **args, t_data *data)
{
	int		i;
	char	*path;

	(void)args;
	i = -1;
	path = mini_getenv("PATH", data->envp);
	if (path == NULL)
	{
		free(path);
		return (utl_error("env: No such file or directory\n", 1));
	}
	free(path);
	while (data->envp[++i] != NULL)
		printf("%s\n", data->envp[i]);
	return (0);
}
