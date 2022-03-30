/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:14 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/30 14:55:44 by jatan            ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

# define KEY 0
# define B_KEY 1
# define A_KEY 2


typedef void	(*t_builtin_funcs)(char **args);

enum e_Type { cmd, arg, redir, pip, file};

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
	char	*cmd;
	char	**args;
	char	*infile;
	char	*outfile;
}	t_cmd_grp;

typedef struct s_data
{
	char			**builtins;
	t_list			*env_list;
	t_list			*tokens;
	int				pipe_number;
	t_list			*cmd_grp;
	int				newline;
	t_builtin_funcs	builtin_funcs[7];
}	t_data;

t_data			*g_data;

void	read_commands(t_data *g_data, char *line);
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
int		exe_pipes(char *input);
void	exe_path(char *input);
t_data	*init_mini(char **envp);
void	heredoc(char *delim);

void	mini_lexer(char *line);
void	parser(char *line);
void	decide_token(char *str);
char	*process_buffer(char *buffer);




#endif
