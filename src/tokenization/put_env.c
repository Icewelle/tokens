/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:37:40 by cluby             #+#    #+#             */
/*   Updated: 2024/10/12 17:22:29 by cluby            ###   ########.fr       */
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

static int	ft_count_words(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == ' ')
			count++;
		i++;
	}
	return (count);
}

static void put_words(char **str, int words)
{
	printf("[%p]\n[%d]\n\n", str, words);
}

static char	**split_env(const char *str)
{
	char	**tenvs;
	int		words;

	words = ft_count_words(str);
	if (!words)
		return (NULL);
	tenvs = malloc((words + 1) * sizeof(char *));
	if (!tenvs)
		return (NULL);
	tenvs[words] = NULL;
	printf("[%p]\n", tenvs);
	put_words(tenvs, words);
	return (tenvs);
}

static void manage_d_quote(t_token *tokens, t_envp *menvp)
{
	char	**tmp;
	int		i;
	
	(void)menvp;
	tmp = split_env(tokens->str);
	if (!tmp)
		return ;
	i = 0;
	while (tmp[i])
	{
		
		printf("tmp[%s]\n", tmp[i]);
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
