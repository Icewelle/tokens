/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 05:43:41 by cluby             #+#    #+#             */
/*   Updated: 2024/10/10 17:51:59 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_blanks(t_token **tokens, const char *prompt, int *i)
{
	if (prompt[*i] == ' ' || prompt[*i] == '\t')
	{
		while (prompt[*i] == ' ' || prompt[*i] == '\t')
			(*i)++;
		t_token_add_back(tokens, t_token_new(" ", BLANK));
	}
}

void	simple_quote(t_token **tokens, const char *prompt, int *i)
{
	int j;
	int is_quote_close;

	is_quote_close = 0;
	if (prompt[*i] == '\'')
	{
		(*i)++;
		j = *i;
		while(prompt[*i] != '\0' && prompt[*i] != '\'')
		{
			(*i)++;
		}
		if (prompt[*i] == '\'')
			is_quote_close = 1;
		if (is_quote_close)
			t_token_add_back(tokens, t_token_new(ft_substr(prompt, j, *i - j), QUOTE));
		(*i)++;
	}
}

void	double_quote(t_token **tokens, const char *prompt, int *i)
{
	int j;
	int is_quote_close;

	is_quote_close = 0;
	if (prompt[*i] == '"')
	{
		(*i)++;
		j = *i;
		while(prompt[*i] != '\0' && prompt[*i] != '"')
		{
			(*i)++;
		}
		if (prompt[*i] == '"')
			is_quote_close = 1;
		if (is_quote_close)
			t_token_add_back(tokens, t_token_new(ft_substr(prompt, j, *i - j), D_QUOTE));
		(*i)++;
	}
}

void	pipe_token(t_token **tokens, const char *prompt, int *i)
{
	if (prompt[*i] == '|')
	{
		t_token_add_back(tokens, t_token_new("|", PIPE));
		(*i)++;
	}
}

void	redirections(t_token **tokens, const char *prompt, int *i)
{
	if (prompt[*i] == '<')
	{
		if (prompt[*i + 1] && prompt[*i + 1] == '<')
		{
			t_token_add_back(tokens, t_token_new("<<", HEREDOC));
			(*i)++;
		}
		else
			t_token_add_back(tokens, t_token_new("<", REDIR_IN));
		(*i)++;
	}
	if (prompt[*i] == '>')
	{
		if (prompt[*i + 1] && prompt[*i + 1] == '>')
		{
			t_token_add_back(tokens, t_token_new(">>", REDIR_APPEND_OUT));
			(*i)++;
		}
		else
			t_token_add_back(tokens, t_token_new(">", REDIR_OUT));
		(*i)++;
	}
}

void	envs(t_token **tokens, const char *prompt, int *i)
{
	int j;

	if (prompt[*i] == '$')
	{
		(*i)++;
		j = *i;
		while(prompt[*i] != '\0' && prompt[*i] != ' ' && prompt[*i] != '\t' && prompt[*i] != '\"' && prompt[*i] != '\'')
			(*i)++;
		t_token_add_back(tokens, t_token_new(ft_substr(prompt, j, *i - j), ENV));
	}
}

void	strings(t_token **tokens, const char *prompt, int *i)
{
	int j;

	j = *i;
	while(prompt[*i] != '\0' && prompt[*i] != ' ' && prompt[*i] != '\t'\
	 && prompt[*i] != '\"' && prompt[*i] != '\'' && prompt[*i] != '|' && \
	 prompt[*i] != '<' && prompt[*i] != '>' && prompt[*i] != '$')
		(*i)++;
	if (j != *i)
		t_token_add_back(tokens, t_token_new(ft_substr(prompt, j, *i - j), STRING));
}

void create_tokens(t_token **tokens ,const char *prompt)
{
	int i;

	i = 0;
	while (prompt[i])
	{
		create_blanks(tokens, prompt, &i);
		simple_quote(tokens, prompt, &i);
		double_quote(tokens, prompt, &i);
		pipe_token(tokens, prompt, &i);
		redirections(tokens, prompt, &i);
		envs(tokens, prompt, &i);
		strings(tokens, prompt, &i);
	}
}
