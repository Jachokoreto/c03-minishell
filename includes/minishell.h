/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:14 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/23 16:27:22 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef void	(*t_builtin_funcs)(char **args);

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

enum e_Type { cmd, arg, redir, pip, file};
typedef struct s_token
{
	enum e_Type	type;
	char		*value;
}	t_token;

typedef struct s_data
{
	char			**builtins;
	t_list			*env_list;
	t_list			*tokens;
	int				newline;
	t_builtin_funcs	builtin_funcs[7];
}	t_data;

t_data	*data;

void	read_commands(t_data *data, char *line);
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
t_data	*init_mini(char **envp);

#endif
