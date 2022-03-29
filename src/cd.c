/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:55 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/21 14:49:16 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **args)
{
	char	buf[256];
	(void)args;
	getcwd(buf, sizeof(buf));
	printf("%s\n", buf);
	chdir(args[0]);
	getcwd(buf, sizeof(buf));
	printf("%s\n", buf);
}
