/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:41:52 by jatan             #+#    #+#             */
/*   Updated: 2022/03/24 19:59:15 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// char	*expand_env_var(char *buf)
// {
// 	int		i;
// 	char	*tmp[4];

// 	i = 0;
// 	while (buf[i])
// 	{
// 		tmp[3] = ft_strchr(&buf[i], '$');
// 		if (tmp[3] == NULL)
// 			break ;
// 		i = tmp[3] - buf + 1;
// 		while (ft_isalnum(buf[i]) == 1 || buf[i] == '_')
// 			i++;
// 		tmp[0] = ft_substr(buf, tmp[3] - buf + 1, i - (tmp[3] - buf + 1));
// 		tmp[1] = ft_substr(buf, 0, tmp[3] - buf + 1);
// 		tmp[2] = ft_strdup(&buf[i]);
// 		buf = ft_strjoin(tmp[1], mini_getenv(tmp[0]));
// 		free(tmp[0]);
// 		tmp[0] = buf;
// 		buf = ft_strjoin(tmp[0], tmp[2]);
// 		free(tmp[0]);
// 		free(tmp[1]);
// 		free(tmp[2]);
// 	}
// 	return (buf);
// }

char	*expand_env_var(char *buf)
{
	char	tmp[4][10000];
	char	*s;
	char	*q[2];

	q[0] = ft_strchr(buf, '\'');
	q[1] = ft_strchr(q[0] + 1, '\'');
	while (buf)
	{
		s = ft_strrchr(buf, '$');
		if (s == NULL)
			break ;
		if (q[0] && q[1] && (q[0] < s && q[1] > s))
		{
			buf++;
			continue ;
		}
		ft_strlcpy(tmp[1], buf, s - buf);
		buf = s + 1;
		while (ft_isalnum(*buf) == 1 || *buf == '_')
			buf++;
		ft_strlcpy(tmp[0], s, buf - s);
		ft_strlcpy(tmp[2], buf, ft_strlen(buf));
		s = ft_strjoin(tmp[1], "weeee");
		buf = ft_strjoin(s, tmp[2]);
		free(s);
	}
	printf("ran\n");
	return (buf);
}

int	main(int argc, char **argv)
{
	char	*str;

	str = expand_env_var(ft_strdup(argv[1]));
	printf("before\t: |%s|\n", argv[1]);
	printf("after\t: |%s|\n", str);
}
