/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:15 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/15 10:48:23 by leu-lee          ###   ########.fr       */
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

int	check_valid_char(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

// starts with i = 1 which means each argument after export
void	loop_env(char **args)
{
	char	**str;
	t_list	*lst;
	int		i;

	i = 0;
	while (args[++i])
	{
		lst = g_data->env_list;
		str = key_value_split(args[i], '=');
		if (str == NULL)
			return ;
		if (check_valid_char(str[0]) == 1)
		{
			printf("`%s': not a valid identifier\n", str[0]);
			continue ;
		}
		set_env(g_data->env_list, str[0], str[1]);
		//free_str_array(str);
	}
	return ;
}

void	export(char **args)
{
	if (args[1] == NULL)
	{
		ft_lstiter(g_data->env_list, print_declarations);
		return ;
	}
	loop_env(args);
}
