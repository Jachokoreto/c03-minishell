/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:50 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 14:36:46 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int	n_flag(char **args)
{
	int	i;
	int	j;
	int	newline_flag;

	i = 0;
	newline_flag = 0;
	while (args[++i])
	{
		j = 1;
		while (args[i][0] == '-' && args[i][j] == 'n')
			j++;
		if (args[i][j - 1] == 'n' && args[i][j] == '\0')
			newline_flag++;
		else
			break ;
	}
	return (newline_flag);
}

int	echo(char **args, void *data)
{
	int		i;
	int		flag;
	char	*tmp;

	if (args[1] == NULL)
		return (1);
	flag = n_flag(args);
	i = flag;
	while (args[++i])
	{
		if (args[i][0] == '~')
			tmp = mini_getenv("HOME", ((t_data *)data)->envp);
		else
			tmp = ft_strdup(args[i]);
		printf("%s", tmp);
		free(tmp);
		if (args[i + 1] != NULL)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
