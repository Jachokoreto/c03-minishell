/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_expand_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 01:49:15 by jatan             #+#    #+#             */
/*   Updated: 2022/04/23 11:31:47 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Iterate through the input line to identify commands and argument in order to
 * categorize each token for the yacc.
 * the spaces will be ignored until reaching an argument before passing it into
 * "get_string_into_buffer". After getting the string, the string will be
 * tokenized.
 */

/**
 * Get_dollar sign counts the index of a string that has a $ infront of it. The
 * length of the string is passed back as a return value.
 */

int	get_dollar_sign(char *buf, int index)
{
	char	*tmp;

	tmp = ft_strchr(&buf[index], '$');
	if (tmp == NULL)
		return (-1);
	return (tmp - buf);
}


/**
 * The strings are joined back up together with the key env string replaced with
 * the value env string. eg for "hi $USER bye", where it becomes "hi jatan bye"
 */

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

/**
 * Temp arrays are innitialized in this function to help with the expansion.
 * tmp[0] is string before the expandable variable, eg "hi $USER", where "hi "
 * is the substring.
 * tmp[1] is the value of the key in the environment linked list.
 * tmp[2] is a duplicated string after the environment variable, eg "hi $USER bye"
 * where " bye"
 */

char	**get_tmps(char *buf, int index, char **envp, char *key)
{
	char	**tmp;

	tmp = ft_calloc(4, sizeof(char *));
	tmp[0] = ft_substr(buf, 0, index);
	tmp[1] = mini_getenv(key, envp);
	tmp[2] = ft_strdup(&buf[index + ft_strlen(key) + 1]);
	return (tmp);
}

/**
 * Expansion of the key value of the environment linked list happens here
 * Buffer is checked for any $ sign which indicates an expansion. This is done
 * in the get_dollar_sign function. The expansion does not occur when a single 
 * quotation is found.
 */

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
