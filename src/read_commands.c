#include "minishell.h"

void	command_list(char *line)
{
	if (!ft_strncmp(line, "echo", 4))
		printf("echo\n");
	if (!ft_strncmp(line, "cd", 2))
		printf("cd\n");
	if (!ft_strncmp(line, "pwd", 3))
		printf("pwd\n");
	if (!ft_strncmp(line, "export", 6))
		printf("export\n");
	if (!ft_strncmp(line, "unset", 5))
		printf("unset\n");
	if (!ft_strncmp(line, "env", 3))
		printf("env\n");
	if (!ft_strncmp(line, "exit", 2))
		printf("exit\n");
	return ;
}

void	read_commands(char *line)
{
	int	i;

	i = 0;
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		i++;
	command_list(line);
	return ;
}
