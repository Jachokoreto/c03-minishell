#include "minishell.h"

t_temp	*init_mini(void)
{
	t_temp	*temp;

	temp = (t_temp *)malloc(sizeof(t_temp));
	temp->builtins = ft_split("echo cd pwd export unset env exit", ' ');
	temp->builtin_funcs[0] = echo;
	temp->builtin_funcs[1] = cd;
	temp->builtin_funcs[2] = pwd;
	// temp->builtin_funcs[3] = export;
	// temp->builtin_funcs[4] = unset;
	// temp->builtin_funcs[5] = env;
	// temp->builtin_funcs[6] = ft_exit;


	return (temp);
}