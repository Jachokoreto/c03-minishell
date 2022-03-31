/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:15 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/31 18:14:03 by leu-lee          ###   ########.fr       */
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

char	**key_value_split(const char *s, char c)
{
	char	**table;
	size_t	index;

	index = 0;
	table = (char **)malloc(sizeof(char *) * (3));
	if (!table)
		return (NULL);
	while (s[index] != c)
		index++;
	index++;
	table[0] = ft_strndup(s, index - 1);
	// printf("%s\n", table[0]);
	table[1] = ft_strndup(s + index, ft_strlen(s) - index);
	// printf("%s\n", table[1]);
	table[2] = NULL;
	return (table);
}

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

	if (args[0] == NULL)
	{
		ft_lstiter(g_data->env_list, print_declarations);
		return ;
	}
	lst = g_data->env_list;
	str = key_value_split(args[0], '=');
	while (lst)
	{
		if (check_key(lst->content, str) == 1)
			return ;
		lst = lst->next;
	}
	env = malloc(sizeof(t_env));
	env->key = str[0];
	env->value = str[1];
	ft_lstadd_back(&g_data->env_list, ft_lstnew(env));
}
