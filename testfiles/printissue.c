# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
#define BUFFER_SIZE 42

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index] != '\0')
		index++;
	return (index);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	int		len;
	char	*heap;

	len = ft_strlen(s1) + ft_strlen(s2);
	heap = malloc(sizeof(char) * (len + 1));
	if (!heap)
		return (NULL);
	index = 0;
	while (*s1)
	{
		heap[index] = *s1;
		index++;
		s1++;
	}
	while (*s2)
	{
		heap[index] = *s2;
		index++;
		s2++;
	}
	heap[index] = '\0';
	return (heap);
}

int	main(void)
{
	int	*fd_arr;
	int	*fd_in;
	int	fd_in2;
	int	fd_out;
	char buffer[256];
	static char *str;
	char	*temp;
	char	*line;
	int	i;
	int	ret;
	int	process;
	int	redir_in; // temp amount
	int	redir_out; // temp amount

	redir_in = 2;
	int	status;
	// fd_in = malloc(sizeof(int)); // resolves the issue.
	char *argv[] = {"/bin/cat", NULL};
	fd_out = open("outfile", O_WRONLY | O_CREAT | O_APPEND, 0777);
	process = fork();
	if (process == 0)
	{
		i = 0;
		while (i < redir_in)
		{
			// write(1, "", 1);
			printf("");		// Not adding printf here would not print the if statement
			printf("before : %d\n", *fd_in);
			*fd_in = open("infile", O_RDONLY, 0777);
			printf("after: %d\n", *fd_in);
			dup2(*fd_in, 0);
			if (!str)
			{
				str = malloc(sizeof(char));
				str[0] = 0;			
			}
			ret = read(*fd_in, buffer, 256);
			buffer[ret] = '\0';
			close(*fd_in);
			temp = ft_strjoin(str, buffer);
			free(temp);
			str = temp;
			i++;
			if (i == redir_in)
			{
				printf("final str: %s\n", str);
				// execve("/bin/cat", argv, NULL);
			}
		}
		//printf("%d\n", i);
	}
	return (0);
}