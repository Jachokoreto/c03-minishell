/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_expand_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 01:49:15 by jatan             #+#    #+#             */
/*   Updated: 2022/04/22 10:33:36 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_dollar_sign(char *buf, int index)
{
	char	*tmp;

	tmp = ft_strchr(&buf[index], '$');
	if (tmp == NULL)
		return (-1);
	return (tmp - buf);
}

char	*join_tmps(char *tmp1, char *tmp2, char *tmp3)
{
	char	*buf;
	char	*tmp;

	if (tmp2 == NULL)
		buf = ft_strdup(tmp1);
	else
		buf = ft_strjoin(tmp1, tmp2);
	tmp = buf;
	buf = ft_strjoin(buf, tmp3);
	free(tmp);
	return (buf);
}

char	**get_tmps(char *buf, int index, char **envp, char *value)
{
	char	**tmp;

	tmp = ft_calloc(4, sizeof(char *));
	tmp[0] = ft_substr(buf, 0, index);
	tmp[1] = mini_getenv(value, envp);
	tmp[2] = ft_strdup(&buf[index + ft_strlen(value) + 1]);
	return (tmp);
}

char	*expand_env_var(char *buf, t_list **penv, char **envp)
{
	char	**tmp;
	int		index;
	char	**data;
	t_list	*env;

	env = *penv;
	index = -1;
	while (buf[++index])
	{
		index = get_dollar_sign(buf, index);
		if (index == -1)
			break ;
		data = env->content;
		env = env->next;
		if (*(data[0]) == '\'')
			continue ;
		tmp = get_tmps(buf, index, envp, data[1]);
		free(buf);
		buf = join_tmps(tmp[0], tmp[1], tmp[2]);
		index += ft_strlen(tmp[1]) - 1;
	}
	free_str_array(tmp);
	ft_lstclear(penv, free_env);
	return (buf);
}
