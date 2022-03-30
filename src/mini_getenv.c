#include <minishell.h>

char	*mini_getenv(char *key)
{
	t_list	*node;
	t_env	*env;
	
	node = g_data->env_list;
	while (node)
	{
		env = node->content;
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
			return(env->value);	
		node = node->next;
	}
	return (NULL);
}
