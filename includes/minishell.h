/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:14 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/10 19:24:05 by leu-lee          ###   ########.fr       */
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

# define KEY 0
# define B_KEY 1
# define A_KEY 2


typedef void	(*t_builtin_funcs)(char **args);

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


typedef struct s_data
{
	char			**builtins;
	int				pipe_number;
	int				fd_type[4];
	t_list			*env_list;
	t_list			*tokens;
	t_list			*cmd_grps;
	t_builtin_funcs	builtin_funcs[7];
}	t_data;

t_data			*g_data;

t_data	*init_mini(char **envp);
void	read_commands(t_list *cmd_grp);
void	echo(char **args);
void	pwd(char **args);
void	cd(char **args);
void	env(char **args);
void	export(char **args);
void	unset(char **args);
void	ft_exit(char **args);
void	shellsignals(void);
char	**get_env_array(void);
char	*mini_getenv(char *key);
char	*join_key_value(char *str1, char *str2, char c);
char	**key_value_split(const char *s, char c);
void	exe_path(char **input);
void	heredocsignals(void);
void	mini_lexer(char *line);
void	parser(char *line);
void	decide_token(char *str);
char	*process_buffer(char *buffer);
void	mini_yacc(void);
void	use_redirections(void); // temp;
void	free_str_array(char **str);
void	utl_move_fd(int fd1, int fd2);
int		exe_pipes(t_list *cmd_grp_list);
int		heredoc(char *delim);
int		utl_strncmp(char *s1, char *s2);


/* Utils */

int		ft_fork(void);
void	ft_kill(pid_t pid, int sig);
void	ft_pipe(int pipefd[2]);
int		ft_open(char *filename, int oflag, int mode);
int		ft_read(int fd, void *buf, size_t count);
void	ft_close(int fd);
void	ft_dup2(int oldfd, int newfd);
void	ft_execve(const char *pathname, char *const argv[], char *const envp[]);
void	ft_tcgetattr(int fd, struct termios *termios_p);
void ft_tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

#endif
