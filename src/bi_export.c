/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:15 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/16 16:15:15 by jatan            ###   ########.fr       */
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
void	loop_env(char **args, t_list *lst)
{
	char	**str;
	int		i;

	i = 0;
	while (args[++i])
	{
		str = key_value_split(args[i], '=');
		if (str == NULL)
			return ;
		if (check_valid_char(str[0]) == 1)
			printf("`%s': not a valid identifier\n", str[0]);
		else
			set_env(lst, str[0], str[1]);
		free_str_array(str);
	}
}

int	export(char **args, void *g_data)
{
	if (args[1] == NULL)
		ft_lstiter(((t_data *)g_data)->env_list, print_declarations);
	else
		loop_env(args, ((t_data *)g_data)->env_list);
	return (0);
}
