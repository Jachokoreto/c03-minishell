/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:15 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/21 16:08:53 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(void *content, char **args)
{
	t_env	*tmp;

	tmp = (t_env *)content;
	if (ft_strncmp(tmp->key, args[0], ft_strlen(args[0])) == 0)
	{
		tmp->value = args[1];
		return (1);
	}
	return (0);
}

void	export(char **args)
{
	char	**str;
	t_env	*env;
	t_list	*lst;

	lst = data->env_list;
	str = ft_split(args[0], '=');
	while (lst)
	{
		if (check_key(lst->content, str) == 1)
			return ;
		lst = lst->next;
	}
	env = malloc(sizeof(t_env));
	env->key = str[0];
	env->value = str[1];
	ft_lstadd_back(&data->env_list, ft_lstnew(env));
}
