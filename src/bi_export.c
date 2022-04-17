/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:15 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 15:35:04 by jatan            ###   ########.fr       */
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

char	**set_env_array(char **array, char *key, char *value)
{
	int		i;
	char	**new_env;

	i = 0;
	while (array[i] != NULL)
	{
		if (ft_strncmp(key, array[i], ft_strlen(key)) == 0
			&& array[i][ft_strlen(key) + 1] == '=')
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

// starts with i = 1 which means each argument after export
void	loop_env(char **args, char ***envp)
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
			*envp = set_env_array(*envp, str[0], str[1]);
		free_str_array(str);
	}
}

int	export(char **args, t_data *data)
{
	int	i;

	if (args[1] == NULL)
	{
		i = -1;
		while (data->envp[++i] != NULL)
			print_declarations(data->envp[i]);
	}
	else
		loop_env(args, &data->envp);
	return (0);
}
