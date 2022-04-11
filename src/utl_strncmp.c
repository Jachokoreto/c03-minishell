#include "minishell.h"

int	utl_strncmp(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0
		&& ft_strlen(s1) == ft_strlen(s2))
		return (0);
	return (1);
}