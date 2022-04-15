#include "minishell.h"

char	**get_env_array(t_data *g_data)
{
	char 	**arr;
	
	arr = NULL;
	t_list	*node;
	t_env	*env;
	int i;

	i = 0;
	arr = ft_calloc(ft_lstsize(g_data->env_list) + 1, sizeof(char *));
	node = g_data->env_list;
	while (node)
	{
		env = node->content;
		arr[i] = join_key_value(env->key, env->value, '=');
		node = node->next;
	}
	return (arr);
}
