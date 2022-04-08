/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:39:06 by jatan             #+#    #+#             */
/*   Updated: 2022/04/08 16:36:01 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*expand_env_var(char *buf, t_list *env)
{
	char	*tmp[4];
	int		index;
	char	**data;

	index = -1;
	while (buf[++index])
	{
		tmp[3] = ft_strchr(&buf[index], '$');
		if (tmp[3] == NULL)
			return (buf);
		data = env->content;
		env = env->next;
		index = tmp[3] - buf;
		if (*(data[0]) == '\'')
			continue ;
		tmp[0] = ft_substr(buf, 0, tmp[3] - buf);
		tmp[1] = mini_getenv(data[1]);
		tmp[2] = ft_strdup(&buf[index + ft_strlen(data[1]) + 1]);
		free(buf);
		if (tmp[1] == NULL)
			buf = ft_strdup(tmp[0]);
		else
			buf = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[0]);
		tmp[0] = buf;
		buf = ft_strjoin(buf, tmp[2]);
		index += ft_strlen(tmp[1]) - 1;
		free(tmp[0]);
		free(tmp[2]);
	}
	return (buf);
}

char	*process_buffer(char *buffer)
{
	t_list	*env;
	char	*i[2];
	char	*qt;
	char	**data;

	i[0] = buffer;
	qt = ft_calloc(2, sizeof(char *));
	env = NULL;
	while (i[0] && *(i[0]))
	{
		if (*i[0] == '$')
		{
			data = ft_calloc(2, sizeof(char *));
			i[1] = i[0] + 1;
			while (ft_isalnum(*i[1]) == 1 || *i[1] == '_')
				i[1]++;
			data[1] = ft_substr(i[0], 1, i[1] - i[0] - 1);
			data[0] = ft_strdup(qt);
			ft_lstadd_back(&env, ft_lstnew(data));
			i[0] = i[1] - 1;
		}
		else if (*i[0] == '\'' || *i[0] == '\"')
		{
			*qt = (*qt != *i[0]) * *qt + (*qt == 0) * *i[0];
			if (*qt == 0 || *qt == *i[0])
				ft_memmove(i[0], i[0] + 1, ft_strlen(i[0]--));
		}
		i[0]++;
	}
	if (env)
		buffer = expand_env_var(buffer, env);
	ft_lstclear(&env, free);
	return (buffer);
}
