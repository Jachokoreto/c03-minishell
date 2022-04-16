/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:38 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/16 16:14:58 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(void *content)
{
	t_env	*tmp;

	tmp = (t_env *)content;
	printf("%s=%s\n", tmp->key, tmp->value);
}

int	env(char **args, void *g_data)
{
	(void)args;
	ft_lstiter(((t_data *)g_data)->env_list, print_list);
	return (0);
}
