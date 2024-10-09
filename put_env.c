/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:37:40 by cluby             #+#    #+#             */
/*   Updated: 2024/10/07 07:59:11 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void replace_env(t_token *tokens, t_envp *menvp)
{
	t_envp *tmp;

	tmp = t_envp_finding(menvp, tokens->str);
	if (tmp)
	{
		free(tokens->str);
		tokens->str = ft_strdup(tmp->value);
	}
	else
	{
		free(tokens->str);
		tokens->str = ft_strdup("");
	}
}

static void	split_env(t_token **tokens)
{
	
}

static void manage_d_quote(t_token **tokens, t_envp *menvp)
{
	split_env(tokens);
	replace_env((*tokens), menvp);
}

void	put_env(t_token **tokens, t_envp *menvp)
{
	while ((*tokens))
	{
		if ((*tokens)->token == ENV)
			replace_env((*tokens), menvp);
		if ((*tokens)->token == D_QUOTE)
			manage_d_quote(tokens, menvp);
		(*tokens) = (*tokens)->next;
	}
}
