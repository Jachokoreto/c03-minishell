#include <minishell.h>

void	execve_stuff(char *input)
{
	char	**path;
	char	*cmd;
	char	*argvec[] = { cmd, input , NULL};
	char	*envVec[] = {"CSC220=Linux", "SECRET=Study Hard", "HELLO=BYE"};
	int		i;

	path = ft_split(mini_getenv("PATH"), ':');
	i = 0;
	while (path)
	{
		cmd = join_key_value(path[i++], input, '/');
		printf("start of execve call %s:\n", cmd);
    	printf("--------------------------------------------------\n");
		if (execve(cmd, argvec, envVec) == -1)
		{
			perror("Could not execute execve");
		}
		printf("Oops, something went wrong!");
	}
}
