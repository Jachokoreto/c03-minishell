#include "minishell.h"

void	last_child(int prev_fd, t_cmd_grp *cmd_grp)
{
	int	redir;

	// printf("last child\n");
	redir = redirections(cmd_grp->retokens);
	if (redir != 1 && redir != 3)
		utl_move_fd(prev_fd, 0);
}

void	first_child(t_cmd_grp *cmd_grp, int *fd)
{
	int	redir;

	// printf("first child\n");
	redir = redirections(cmd_grp->retokens);
	if (redir != 2 && redir != 3)
		utl_move_fd(fd[1], 1);
	ft_close(fd[0]);
}

void	middle_child(int prev_fd, t_cmd_grp *cmd_grp, int *fd)
{
	int	redir;

	// printf("mid child\n");
	redir = redirections(cmd_grp->retokens);
	if (redir != 1 && redir != 3)
		utl_move_fd(prev_fd, 0);
	if (redir != 2 && redir != 3)
		utl_move_fd(fd[1], 1);
	ft_close(fd[0]);
}
