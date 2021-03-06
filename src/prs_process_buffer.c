/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:39:06 by jatan             #+#    #+#             */
/*   Updated: 2022/04/30 17:06:46 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function that handles the expansion of variable when a dollar sign is
 * found in the string buffer. Length of the expanded variable will be counted.
 * After getting counted itself, the substring of the counted string will be
 * extracted and placed into env linked list through lstadd_back.
 *
 * For example: Assuming $USER is passed as string, USER is extracted as
 * substring and placed into the env linked list.
 */
static char	*handle_dollar_sign(t_list **env, char *i_0, char *qt)
{
	char	**data;
	char	*i_1;

	data = ft_calloc(2, sizeof(char *));
	i_1 = i_0 + 1;
	if (*i_1 == '?')
		data[1] = ft_strdup("?");
	else if (ft_isdigit(*i_1) == 1)
		data[1] = ft_substr(i_0, 1, 1);
	else
	{
		while (ft_isalnum(*i_1) == 1 || *i_1 == '_')
			i_1++;
		data[1] = ft_substr(i_0, 1, i_1 - i_0 - 1);
	}
	data[0] = ft_strdup(qt);
	ft_lstadd_back(env, ft_lstnew(data));
	return (i_1 - 1);
}

/**
 * The function that handles the double quotations and single quotations.
 * The function consist of a ternary function that gets called twice.
 * When a quotation is found, the string buffer itself will undergo memmmove
 * which in the end would remove the quotation itself.
 */
static char	*handle_quotes(char *qt, char *i)
{
	*qt = (*qt != *i) * *qt + (*qt == 0) * *i;
	if ((*qt == 0 || *qt == *i))
	{
		ft_memmove(i, i + 1, ft_strlen(i));
		i--;
	}
	return (i);
}

char	*check_buffer(char *buffer)
{
	if (buffer != NULL && *buffer == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

/**
 * The process buffer handles expansion and quotes of the string.
 * It is both handled by its respective functions.
 * Once expansion and quotations are done, the buffer is returned back as the
 * token value of the t_token linked list.
 */
char	*process_buffer(char *buffer, char **envp)
{
	t_list	*env_list;
	char	*i;
	char	*qt;

	i = buffer;
	env_list = NULL;
	qt = ft_calloc(2, sizeof(char));
	while (i && *(i))
	{
		if (*i == '$')
			i = handle_dollar_sign(&env_list, i, qt);
		else if (*i == '\'' || *i == '\"')
			i = handle_quotes(qt, i);
		i++;
	}
	if (env_list != NULL)
	{
		buffer = expand_env_var(buffer, &env_list, envp);
		ft_lstclear(&env_list, free_env);
		buffer = check_buffer(buffer);
	}
	free(qt);
	return (buffer);
}
