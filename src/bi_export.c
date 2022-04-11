/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:15 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/11 21:50:49 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

// LATER FIX IT PLS 
void	print_declarations(void *content)
{
	t_env	*tmp;

	tmp = (t_env *)content;
	if (ft_strncmp(tmp->key, "_", ft_strlen(tmp->key)) != 0)
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
}

void	check_key(t_list *lst, char **args)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = (t_env *)lst->content;
		if (utl_strncmp(tmp->key, args[0]) == 0)
		{
			tmp->value = args[1];
			return ;
		}
		lst = lst->next;
	}
	tmp = ft_calloc(1, sizeof(t_env));
	tmp->key = args[0];
	tmp->value = args[1];
	ft_lstadd_back(&g_data->env_list, ft_lstnew(tmp));
}

void	export(char **args)
{
	char	**str;
	t_list	*lst;
	int		i;

	if (args[1] == NULL)
	{
		ft_lstiter(g_data->env_list, print_declarations);
		return ;
	}
	i = 0;
	while (args[++i])
	{
		lst = g_data->env_list;
		str = key_value_split(args[i], '=');
		if (str == NULL)
			return ;
		check_key(g_data->env_list, str);
		free_str_array(str);
	}
	return ;
}
