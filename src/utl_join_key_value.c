#include "minishell.h"

char	*join_key_value(char *str1, char *str2, char c)
{
	int			i;
	char		*heap;
	int			len;

	len = ft_strlen(str1) + ft_strlen(str2) + 2;
	heap = (char *)ft_calloc(len, sizeof(char));
	if (!heap)
		return (NULL);
	i = 0;	
	while (str1 && *str1)
		heap[i++] = *str1++;
	heap[i++] = c;
	while (str2 && *str2)
		heap[i++] = *str2++;
	heap[i] = '\0';
	return (heap);
}