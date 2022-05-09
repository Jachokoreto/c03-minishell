/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:17:21 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/08 13:35:36 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc(char *delim, int i)
{
	char		*str;
	char		*file;
	char		*line;
	int			fd_temp;

	file = heredoc_file(i);
	fd_temp = ft_open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		line = readline("heredoc > ");
		if (line == NULL)
			break ;
		if (utl_strncmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		str = ft_strjoin(line, "\n");
		ft_putstr_fd(str, fd_temp);
		free(str);
		free(line);
	}
	close(fd_temp);
	return (file);
}

/**
 * Heredocs are processed before execution. This is because if 2 heredocs were to
 * run at the child processes, they would run two of them together which is not
 * working as intended for bash. Hence, the heredoc file is processed beforehand
 * before passing it as a redirection to combat this.
 */

void	process_heredoc(t_list *cmd_grp_list, t_list *retokens)
{
	t_token		*token;
	t_cmd_grp	*cmd_grp;
	char		*filename;
	int			i;

	while (cmd_grp_list != NULL)
	{
		i = 0;
		cmd_grp = cmd_grp_list->content;
		while (retokens != NULL)
		{
			token = retokens->content;
			if (token->type == delim)
			{
				filename = heredoc(token->value, i++);
				token->type = infile;
				free(token->value);
				token->value = filename;
			}
			retokens = retokens->next;
		}
		cmd_grp_list = cmd_grp_list->next;
	}
}

/**
 * The start of the execution of what have been parsed.
 * The fd input and output of the parent process will be saved temporarily.
 * This is done so that the builtins can be run without any child process
 * assuming there is only one command group.
 * If there is more than one command group, pipes will be used to transfer
 * the output to the child processes.
 */

void	executor(t_list *cmd_grp_list, t_data *data)
{
	int			saved_fd[2];
	t_cmd_grp	*cmd_grp;
	int			pipe_num;

	signal(SIGINT, SIG_IGN);
	if (cmd_grp_list == NULL)
		return ;
	saved_fd[0] = dup(0);
	saved_fd[1] = dup(1);
	cmd_grp = cmd_grp_list->content;
	pipe_num = ft_lstsize(data->cmd_grps) - 1;
	process_heredoc(cmd_grp_list, data->tokens);
	if (pipe_num > 0)
		exe_pipe_cmds(cmd_grp_list, data, pipe_num);
	else
	{
		cmd_grp = cmd_grp_list->content;
		if (redirections(data->tokens) != -1)
			exe_commands(cmd_grp, data, pipe_num);
	}
	utl_move_fd(saved_fd[1], 1);
	utl_move_fd(saved_fd[0], 0);
}
