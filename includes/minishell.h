/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:14 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/01 14:51:41 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "styling.h"

# define FIRST 0
# define MIDDLE 1
# define LAST 2

enum e_Type { arg, redir, pip, infile, outfile1, outfile2, delim};

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_token
{
	enum e_Type	type;
	char		*value;
}	t_token;

typedef struct s_cmd_grp
{
	char	**args;
	t_list	*retokens;
}	t_cmd_grp;

struct		s_data;
typedef int	(*t_builtin_funcs)(char **args, struct s_data *data);

typedef struct s_data
{
	char			**builtins;
	char			**envp;
	int				exit_status;
	t_list			*env_list;
	t_list			*tokens;
	t_list			*cmd_grps;
	t_builtin_funcs	builtin_funcs[7];
}	t_data;

int			g_exit;

/* Builtins */
int		echo(char **args, t_data *data);
int		pwd(char **args, t_data *data);
int		cd(char **args, t_data *data);
int		env(char **args, t_data *data);
int		export(char **args, t_data *data);
int		unset(char **args, t_data *data);
int		ft_exit(char **args, t_data *data);

/* Parsing */
t_data	*init_mini(char **envp);
int		decide_token(char *str, t_data *data);
int		mini_lexer(char *line, t_data *data);
void	mini_yacc(t_data *data);
char	*process_buffer(char *buffer, char **envp);
char	*expand_env_var(char *buf, t_list **penv, char **envp);

/* Executor */
void	executor(t_list *cmd_grp, t_data *data);
void	exe_commands(t_cmd_grp *cmd_grp, t_data *data, int pipe_num);
int		redirections(t_list *retokens);
int		exe_builtins(t_cmd_grp *cmd_grp, t_data *data);
int		exe_pipe_cmds(t_list *cmd_grp_list, t_data *data, int pipe_num);
int		heredoc(char *delim);

/* Signals */
void	shellsignals(void);

/* Free functions */
void	free_list(void);
void	free_str_array(char **str);
void	free_env(void *content);
void	free_cmd_grp(void *content);
void	free_token(void *content);

/* Function Utils */
char	**get_env_array(t_data *data);
char	*mini_getenv(char *key, char **envp);
char	*join_key_value(char *str1, char *str2, char c);
char	**key_value_split(const char *s, char c);
void	utl_move_fd(int fd1, int fd2);
void	set_env(t_list *lst, char *key, char *value);
int		utl_strncmp(char *s1, char *s2);
int		utl_error(char *msg, int error_num);
int		check_valid_char(char *str);

/* General utils */

int		ft_chdir(const char *path);
int		ft_fork(void);
void	ft_kill(pid_t pid, int sig);
void	ft_pipe(int pipefd[2]);
int		ft_open(char *filename, int oflag, int mode);
int		ft_read(int fd, void *buf, size_t count);
void	ft_close(int fd);
void	ft_dup2(int oldfd, int newfd);
void	ft_execve(const char *pathname, char *const argv[], char *const envp[]);
void	ft_tcgetattr(int fd, struct termios *termios_p);
void	ft_tcsetattr(int fd, int optional_actions,
			const struct termios *termios_p);
void	ft_dup(int oldfd);
void	ft_unlink(const char *pathname);
void	ft_free_all(t_data *data);
void	ft_free(char **str);

#endif
