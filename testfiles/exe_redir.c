#include <minishell.h>

char	**get_infiles()
{
	char	**infiles;
	// temp mallocs
	// change to linked list
	infiles = malloc(sizeof(char *) * 3);
	infiles[0] = "infile";
	infiles[1] = "infile1";
	return (infiles);
}

char	**get_outfiles()
{
	char	**outfiles;
	// temp mallocs
	// change to linked list
	outfiles = malloc(sizeof(char *) * 3);
	outfiles[0] = "0tempfile";
	outfiles[1] = "1outfile2";
	return (outfiles);
}

void	output_redir(int redir_out)
{
	int	i;
	int	fd_out;
	char	**outfiles;

	outfiles = get_outfiles();
	i = -1;
	printf("Redir out\n");
	while (++i < redir_out)
	{ // might need to change to linked list
		if (outfiles[i][0] == '0')
		{
			if (i == 0)
				fd_out = ft_open( &outfiles[0][1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (i == 1)
				fd_out = ft_open( &outfiles[1][1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		}
		else
		{
			if (i == 0)
				fd_out = ft_open( &outfiles[0][1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (i == 1)
				fd_out = ft_open( &outfiles[1][1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		}
		dup2(fd_out, 1);
		close(fd_out);
	}
	return ;
}

void	input_redir(int redir_in)
{
	int	i;
	int	fd_in;
	char **infiles;

	infiles = get_infiles();
	i = -1;
	while (++i < redir_in)
	{
		// heredoc should be here or does it? Does it? Hmm
		if (i == 0)
			fd_in = ft_open( infiles[0], O_RDWR, 0777);
		if (i == 1)
			fd_in = ft_open( infiles[1], O_RDWR, 0777);
		dup2(fd_in, 0);
		close(fd_in);
	}
	return ;
}

void	use_redirections(void)
{
	int	redir_in;
	int	redir_out;

	redir_in = 0; // temps here
	redir_out = 1;
	if (redir_in > 0)
		input_redir(redir_in);
	if (redir_out > 0)
		output_redir(redir_out);
	return ;
}
