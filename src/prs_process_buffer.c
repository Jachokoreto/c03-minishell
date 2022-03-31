/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:39:06 by jatan             #+#    #+#             */
/*   Updated: 2022/03/30 14:17:19 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env_var(char *buf, t_list *env)
{
	char	*tmp[4];
	int		index;
	char	**data;

	index = -1;
	printf("%s\n", buf);
	while (buf[++index])
	{
		tmp[3] = ft_strchr(&buf[index], '$'); // get $ pos
		if (tmp[3] == NULL)
			return (buf);
		data = env->content;
		env = env->next;
		index = tmp[3] - buf;
		printf("index: %d\n", index);
		if ('\"' == '\'')
			continue ;
		tmp[0] = ft_substr(buf, 0, tmp[3] - buf); // get string before $
		tmp[1] = mini_getenv(data[1]);
		printf("data[1]: %s\ntmp[0]:%s\ntmp[1]:%s\n", data[1], tmp[0], tmp[1]);
		tmp[2] = ft_strdup(&buf[index + ft_strlen(data[1]) + 1]); // get string after $ name
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
	char	*idx[2];
	char	qt;
	char	**data;

	idx[0] = buffer;
	qt = 0;
	env = NULL;
	while (idx[0] && *idx[0])
	{
		if (*idx[0] == '$')
		{
			data = malloc(sizeof(char *) * 2);
			idx[1] = idx[0] + 1;
			while (ft_isalnum(*idx[1]) == 1 || *idx[1] == '_')
				idx[1]++;
			data[1] = ft_substr(idx[0], 1, idx[1] - idx[0] - 1);
			// data[0] = qt;
			ft_lstadd_back(&env, ft_lstnew(data));
			idx[0] = idx[1] - 1;
		}
		else if (*idx[0] == '\'' || *idx[0] == '\"')
		{
			qt = (qt != *idx[0]) * qt + (qt != *idx[0] && qt == 0) * *idx[0];
			if (qt == 0 || qt == *idx[0])
				ft_memmove(idx[0], idx[0] + 1, ft_strlen(idx[0] - 1));
		}
		idx[0]++;
	}
	printf("buffer: %s\n", buffer);
	if (env)
		buffer = expand_env_var(buffer, env);
	ft_lstclear(&env, free);
	return (buffer);
}
