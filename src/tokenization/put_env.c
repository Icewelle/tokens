/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:37:40 by cluby             #+#    #+#             */
/*   Updated: 2024/10/10 18:08:05 by cluby            ###   ########.fr       */
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

static void manage_d_quote(t_token *tokens, t_envp *menvp)
{
	char	**tmp;
	int		i;
	
	(void)menvp;
	tmp = ft_split(tokens->str, '$');
	if (!tmp)
		return ;
	i = 0;
	while (tmp[i])
	{
		
		printf("[%s]\n", tmp[i]);
		i++;
	}
}

void	put_env(t_token **tokens, t_envp *menvp)
{
	t_token	*tmp;
	
	tmp = (*tokens);
	while (tmp)
	{
		if (tmp->token == ENV)
			replace_env(tmp, menvp);
		if (tmp->token == D_QUOTE)
			manage_d_quote(tmp, menvp);
		tmp = tmp->next;
	}
}
