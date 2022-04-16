/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:47:28 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/16 18:49:14 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	pwd(char **args, void *data)
{
	char	*buf;

	(void)args;
	(void)data;
	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
