/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:14 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/23 14:45:37 by jatan            ###   ########.fr       */
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

# define KEY 0
# define B_KEY 1
# define A_KEY 2



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
	char	**args; // args[0] = cmd, args[n] = arguments
	t_list	*retokens;
}	t_cmd_grp;

struct	s_data;
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

int	g_exit;

/* utl_init_mini.c */
t_data	*init_mini(char **envp);

/* bi_*.c */
int		echo(char **args, t_data *data);
int		pwd(char **args, t_data *data);
int		cd(char **args, t_data *data);
int		env(char **args, t_data *data);
int		export(char **args, t_data *data);
int		unset(char **args, t_data *data);
int		ft_exit(char **args, t_data *data);

/* shellsignals.c */
void	shellsignals(void);

/* utl_*.c */
char	**get_env_array(t_data *data);
char	*mini_getenv(char *key, char **envp);
char	*join_key_value(char *str1, char *str2, char c);
char	**key_value_split(const char *s, char c);
void	utl_move_fd(int fd1, int fd2);
int		utl_strncmp(char *s1, char *s2);
void	heredocsignals(void);

void	mini_lexer(char *line, t_data *g_data);
void	decide_token(char *str, t_data *g_data);
char	*process_buffer(char *buffer, char **envp);
char	*expand_env_var(char *buf, t_list **penv, char **envp);

void	mini_yacc(t_data *g_data);


/* executor.c */
void	executor(t_list *cmd_grp, t_data *data);
void	use_redirections(void); // temp;
int		redirections(t_list *retokens);
void	first_child(t_cmd_grp *cmd_grp, int *fd);
void	middle_child(int prev_fd, t_cmd_grp *cmd_grp, int *fd);
void	last_child(int prev_fd, t_cmd_grp *cmd_grp);
int		exe_builtins(t_cmd_grp *cmd_grp, t_data *g_data);
void	exe_path(char **input, char **envp, char **path);
int		exe_pipe_cmds(t_list *cmd_grp_list, t_data *g_data, int pipe_num);
void	exe_commands(t_cmd_grp *cmd_grp, t_data *g_data, int pipe_num);
int		heredoc(char *delim);

void	free_list(void);
void	free_str_array(char **str);
void	free_env(void *content);
void	free_cmd_grp(void *content);
void	free_token(void *content);
void	set_env(t_list *lst, char *key, char *value);

/* utl_env_array.c */
// char	**del_env(char **array, char *key);
// char	**set_env_array(char **array, char *key, char *value);


/* Utils */

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
void	ft_free_all(t_data *g_data);
void	ft_free(char **str);

#endif
