/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:41 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/09 10:36:37 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_launch_minishell(char *line, t_data *data)
{
	mini_lexer(line, data);
	mini_yacc(data);
	executor(data->cmd_grps, data);
	ft_lstclear(&data->tokens, free_token);
	ft_lstclear(&data->cmd_grps, free_cmd_grp);
	unlink(".heredocfile");
	exit(g_exit);
}

static void	reset_data(t_data *data)
{
	struct stat	buf;
	int			i;
	char		*str;

	ft_lstclear(&data->tokens, free_token);
	ft_lstclear(&data->cmd_grps, free_cmd_grp);
	i = 0;
	while (1)
	{
		str = heredoc_file(i++);
		if (stat(str, &buf) == -1)
		{
			free(str);
			break ;
		}
		unlink(str);
		free(str);
	}
}

static void	print_welcome(void)
{
	int		fd;
	char	buffer[1];

	printf(""
		RED"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗    ██╗    \n"
		ORG"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║    ██║    \n"
		YLW"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║    ██║    \n"
		GRN"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║    ██║    \n"
		BLU"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗██████╗██████╗\n"
		IDG"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚═════╝╚═════╝\n"
		VLT" 				by: jatan & leu-lee   	"RESET"\n\n");
	fd = ft_open("./.woof.txt", O_RDONLY, 0666);
	while (ft_read(fd, buffer, 1))
		write(1, buffer, 1);
	close(fd);
}

static char	*manage_readline(char *prompt, t_data *data)
{
	char	*line;
	int		i;

	(void)data;
	line = readline(prompt);
	if (line == NULL)
	{
		ft_free_all(data);
		exit(10);
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ')
		{
			add_history(line);
			return (line);
		}
	}
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data		*data;

	(void)argc;
	(void)argv;
	data = init_mini(envp);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
		ft_launch_minishell(argv[2], data);
	print_welcome();
	while (1)
	{
		shellsignals();
		line = manage_readline("\033[035mminishell🔪\033[0m ", data);
		if (mini_lexer(line, data) == 0)
		{
			mini_yacc(data);
			executor(data->cmd_grps, data);
		}
		reset_data(data);
		free(line);
	}
}
