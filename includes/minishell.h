/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:14 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/21 14:45:14 by leu-lee          ###   ########.fr       */
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

typedef void (*t_builtin_funcs)(char **args);

typedef struct s_env
{
	char 	*key;
	char	*value;
}	t_env;

typedef struct s_data
{
	t_list			*env_list;
	char			**builtins;
	t_builtin_funcs	builtin_funcs[7];
}	t_data;

t_data	*data;

void	read_commands(t_data *data, char *line);
void	echo(char **args);
void	pwd(char **args);
void	cd(char **args);
void	env(char **args);
t_data	*init_mini(char **envp);

#endif
