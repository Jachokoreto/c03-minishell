#include "minishell.h"

void	heredoc(char *delim)
{
	char		*str;
	char		*temp;
	char		*line;

	str = malloc(sizeof(char));
	if (delim == NULL)
		return ; 
	while (1)
	{
		line = readline("heredoc > ");
		if (line == NULL)
			continue ;
		if (!str)
		{
			str = ft_strdup(line);
			// printf("hi\n");
		}
		else 
		// if (!(ft_strncmp(line, delim, ft_strlen(delim) == 0)))
		{
			if ((strncmp(line, ft_strjoin(delim, "\n"), ft_strlen(line)) == 0))
			// printf("line: %s\n", line);
			temp = ft_strdup(line);
			printf("temp: |%s|\n", temp);
			printf("str: |%s|\n", str);
			temp = ft_strjoin(str, line);
			str = ft_strdup(temp);
			str = ft_strjoin(str, "\n");
			free(temp);
		}
		if ((strncmp(line, ft_strjoin(delim, "\n"), ft_strlen(line)) == 0))
			break;
		
	}
	printf("%s\n", str);
	return ;
}
