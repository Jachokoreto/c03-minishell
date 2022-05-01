/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ult_mini_getenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:47:12 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/01 11:46:17 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*mini_getenv(char *key, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && key != NULL)
	{
		if (ft_strncmp(key, envp[i], ft_strlen(key)) == 0
			&& envp[i][ft_strlen(key)] == '=')
			return (ft_strdup(&envp[i][ft_strlen(key) + 1]));
		i++;
	}
	return (NULL);
}
