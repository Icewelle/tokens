/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:37:40 by cluby             #+#    #+#             */
/*   Updated: 2024/10/19 11:49:19 by cluby            ###   ########.fr       */
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

static char	**split_env(const char *str)
{
	int len = strlen(str);
    int i = 0, word_count = 0;
    char **result = (char **)malloc((len + 1) * sizeof(char *));  // Allocate enough memory

    while (i < len) {
        if (str[i] == ' ' || str[i] == '\t') {
            result[word_count] = (char *)malloc(2 * sizeof(char));  // Space or tab is a single char plus null terminator
            result[word_count][0] = str[i];
            result[word_count][1] = '\0';  // Null-terminate the string
            word_count++;
            i++;
            continue;
        }
        int start = i;
        if (str[i] == '$') {
            start = i++;  // Skip the '$'
            while (i < len && (str[i] != ' ' && str[i] != '\t' && str[i] != '$')) {
                i++;
            }
        } else {
            while (i < len && (str[i] != ' ' && str[i] != '\t' && str[i] != '$')) {
                i++;
            }
        }
        int word_len = i - start;
        if (word_len > 0) {
            result[word_count] = (char *)malloc((word_len + 1) * sizeof(char));
            strncpy(result[word_count], str + start, word_len);
            result[word_count][word_len] = '\0';  // Null-terminate the string
            word_count++;
        }
    }
    result[word_count] = NULL;
    return result;
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
