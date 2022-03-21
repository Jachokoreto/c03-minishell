#include "minishell.h"

void	print_list(void *content)
{
	t_env *tmp;
	
	tmp = (t_env *)content;
	printf("%s=", tmp->key);
	printf("%s\n", tmp->value);
}

void	env(char **args)
{
	(void)args;
	ft_lstiter(data->env_list, print_list);
}