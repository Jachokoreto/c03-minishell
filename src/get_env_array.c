#include "minishell.h"

char	*join_key_value(char *str1, char *str2, char c)
{
	int			i;
	char		*heap;
	int			len;

	len = strlen(str1) + strlen(str2) + 2;
	heap = (char *)malloc(sizeof(char) * len);
	if (!heap)
		return (NULL);
	i = 0;	
	while (*str1)
		heap[i++] = *str1++;
	heap[i++] = c;
	while (*str2)
		heap[i++] = *str2++;
	heap[i] = '\0';
	return (heap);
}

char	**get_env_array(void)
{
	char 	**arr;
	t_list	*node;
	t_env	*env;
	int i;

	i = 0;
	arr = malloc(sizeof(char *) * ft_lstsize(data->env_list) + 1);
	node = data->env_list;
	while (node)
	{
		env = node->content;
		arr[i] = join_key_value(env->key, env->value, '=');
		node = node->next;
		//printf("%s\n", arr[i++]);
	}
	return (arr);
}
