#include "minishell.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(content);
}

void	free_cmd_grp(void *content)
{
	t_cmd_grp	*cmd_grp;

	cmd_grp = (t_cmd_grp *)content;
	// while (cmd_grp->args[i])
		// free(cmd_grp->args[i++]);
	free(cmd_grp->args);
	// ft_lstclear(&cmd_grp->retokens, free_token);
	free(content);
}

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(content);
}
