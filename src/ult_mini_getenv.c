#include <minishell.h>

char	*mini_getenv(char *key)
{
	t_list	*node;
	t_env	*env;
	
	node = g_data->env_list;
	while (node)
	{
		env = node->content;
		if (utl_strncmp(env->key, key) == 0)
			return(env->value);
		node = node->next;

	}
	return (NULL);
}
