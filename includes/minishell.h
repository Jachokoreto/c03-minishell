#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"
# include "libft.h"
# include <readline/readline.h>

typedef void (*t_builtin_funcs)(char **args);

typedef struct s_temp
{
	char			**builtins;
	t_builtin_funcs	builtin_funcs[7];
}	t_temp;

int		main(int argc, char **argv);
void	read_commands(t_temp *temp, char *line);
void	echo(char **args);
void	pwd(char **args);
void	cd(char **args);
t_temp	*init_mini(void);

#endif
