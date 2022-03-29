/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:38 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/21 14:54:18 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(void *content)
{
	t_env	*tmp;

	tmp = (t_env *)content;
	printf("%s=", tmp->key);
	printf("%s\n", tmp->value);
}

void	env(char **args)
{
	(void)args;
	ft_lstiter(data->env_list, print_list);
}
