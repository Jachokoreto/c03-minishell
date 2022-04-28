/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:44:05 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/28 11:38:32 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_builtins(t_cmd_grp *cmd_grp, t_data *data)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (utl_strncmp(cmd_grp->args[0], data->builtins[i]) == 0)
		{
			data->builtin_funcs[i](cmd_grp->args, data);
			return (0);
		}
	}
	return (1);
}
