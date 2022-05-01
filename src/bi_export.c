/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:15 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/01 12:31:26 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_declarations(char *env)
{
	char	**tmp;

	tmp = key_value_split(env, '=');
	if (ft_strncmp(tmp[0], "_", ft_strlen(tmp[0])) != 0)
		printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
	free_str_array(tmp);
}

char	**set_env_array(char **array, char *key, char *value)
{
	int		i;
	char	**new_env;

	i = 0;
	while (array[i] != NULL)
	{
		if (ft_strncmp(key, array[i], ft_strlen(key)) == 0
			&& array[i][ft_strlen(key)] == '=')
		{
			free(array[i]);
			array[i] = join_key_value(key, value, '=');
			return (array);
		}
		i++;
	}
	new_env = ft_calloc(i + 2, sizeof(char *));
	new_env[i] = join_key_value(key, value, '=');
	while (--i >= 0)
		new_env[i] = ft_strdup(array[i]);
	free_str_array(array);
	return (new_env);
}

void	loop_env(char **args, char ***envp, int i)
{
	char	**str;

	str = key_value_split(args[i], '=');
	if (str == NULL)
	{
		if (check_valid_char(args[1]) == 1)
		{
			ft_putstr_fd(args[1], 2);
			utl_error(": not a valid identifier\n", 1);
		}
		free_str_array(str);
		return ;
	}
	if (check_valid_char(str[0]) == 1)
	{
		ft_putstr_fd(str[0], 2);
		utl_error(": not a valid identifier\n", 1);
	}
	else
		*envp = set_env_array(*envp, str[0], str[1]);
	free_str_array(str);
}

int	export(char **args, t_data *data)
{
	int	i;

	if (args[1] == NULL || args[1][0] == '#')
	{
		i = -1;
		while (data->envp[++i] != NULL)
			print_declarations(data->envp[i]);
	}
	else
	{
		i = 0;
		while (args[++i])
			loop_env(args, &data->envp, i);
	}
	return (0);
}
