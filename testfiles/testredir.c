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
	heap = ft_calloc(sizeof(char) * (len + 1));
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
	int	fd_in;
	int	fd_in2;
	int	fd_out;
	int	fd_out2;
	char buffer[256];
	static char *str;
	char	*temp;
	char	*line;
	int	i;
	int	ret;
	int	process[2];
	int	redir_in; // temp amount
	int	redir_out; // temp amount
	int	status;
	char *argv[] = {"/bin/cat", NULL};

	redir_in = 2;
	redir_out = 2;
	process[0] = fork();
	if (process[0] == 0)
	{
		i = -1;
		while (++i < redir_in)
		{
			fd_in = open("infile1", O_RDONLY, 0777);
			dup2(fd_in, 0);
			if (!str)
			{
				str = ft_calloc(sizeof(char));
				str[0] = 0;			
			}
			ret = read(fd_in, buffer, 256);
			buffer[ret] = '\0';
			close(fd_in);
			temp = ft_strjoin(str, buffer);
			str = temp;
			free(temp);
		}
		fd_in = open("virtual", O_CREAT | O_RDWR | O_APPEND, 0777);
		write(fd_in, str, ft_strlen(str));
		close(fd_in);
		fd_in2 = open("virtual", O_RDONLY, 0777);
		dup2(fd_in2, 0);
		close(fd_in2);

		// files will be passed in later
		process[1] = fork();
		if (process[1] == 0)
		{
			fd_out = open("outfile", O_WRONLY | O_CREAT | O_APPEND, 0777);
			dup2(fd_out, 1);
			close(fd_out);
			if (execve("/bin/cat", argv, NULL) == -1)
				printf("boo\n");
		}
		// sleep(1);
		// fd_out = open("outfile", O_RDONLY, 0777);
		// ret	 = read(1, buffer, 256);
		// buffer[ret] = '\0';
		// fd_out2 = open("outfile2", O_WRONLY | O_CREAT | O_APPEND, 0777);

		// write(fd_out2, buffer, ft_strlen(buffer));
		// fd_out = open("outfile", O_WRONLY | O_CREAT | O_APPEND, 0777);
		// dup2(fd_out, 1);
		// close(fd_out);
	}
	return (0);
}
