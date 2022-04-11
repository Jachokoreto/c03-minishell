/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:38 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/09 15:43:36 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(void *content)
{
	t_env	*tmp;

	tmp = (t_env *)content;
	printf("%s=%s\n", tmp->key, tmp->value);
}

void	env(char **args)
{
	(void)args;
	ft_lstiter(g_data->env_list, print_list);
}
