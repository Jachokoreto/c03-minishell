#include "minishell.h"

// int	ft_countwords(const char *s, char c)
// {
// 	size_t	i;
// 	size_t	words;

// 	i = 0;
// 	words = 0;
// 	while (s[i] != '\0')
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i] != '\0')
// 			words++;
// 		while (s[i] && s[i] != c)
// 			i++;
// 	}
// 	return (words);
// }

void	echo(char **args)
{
	printf("%s\n", args[0]);
}