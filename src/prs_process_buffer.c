/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:39:06 by jatan             #+#    #+#             */
/*   Updated: 2022/04/22 14:23:10 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	handle_dollar_sign(t_list **env, char *i_0, char qt)
{
	char	**data;
	char	*i_1;

	data = ft_calloc(2, sizeof(char *));
	i_1 = i_0 + 1;
	while (ft_isalnum(*i_1) == 1 || *i_1 == '_')
		i_1++;
	data[1] = ft_substr(i_0, 1, i_1 - i_0 - 1);
	data[0] = &qt;
	ft_lstadd_back(env, ft_lstnew(data));
	i_0 = i_1 - 1;
}

void	handle_quotes(char *qt, char *i)
{
	*qt = (*qt != *i) * *qt + (*qt == 0) * *i;
	if ((*qt == 0 || *qt == *i))
	{
		ft_memmove(i, i + 1, ft_strlen(i));
		i--;
	}
}

char	*process_buffer(char *buffer, char **envp)
{
	t_list	*env;
	char	*i;
	char	qt;

	i = buffer;
	env = NULL;
	qt = 0;
	while (i && *(i))
	{
		if (*i == '$')
			handle_dollar_sign(&env, i, qt);
		else if (*i == '\'' || *i == '\"')
		{
			handle_quotes(&qt, i);
		}
		i++;
	}
	if (env != NULL)
		buffer = expand_env_var(buffer, &env, envp);
	return (buffer);
}
