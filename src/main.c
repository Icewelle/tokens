#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	t_envp	*menvp;
	t_token	*tokens;
	char	*path;
	char	*prompt;

	(void)argc;
	(void)argv;
	menvp = t_envp_init(envp);
	while (1)
	{
		path = getcwd(NULL, 0);
		path = ft_strjoin(path, " $ ");
		prompt = readline(path);
		add_history(prompt);
		if (ft_strlen(prompt))
		{
			tokens = t_token_new("", STRING);
			create_tokens(&tokens, prompt);
			put_env(&tokens, menvp);
			while (tokens)
			{
				printf("[%s] = ", tokens->str);
				if (tokens->token == COMMAND)
					printf("[COMMAND]\n");
				if (tokens->token == STRING)
					printf("[STRING]\n");
				if (tokens->token == REDIR_APPEND_OUT)
					printf("[REDIR_APPEND_OUT]\n");
				if (tokens->token == REDIR_IN)
					printf("[REDIR_IN]\n");
				if (tokens->token == REDIR_OUT)
					printf("[REDIR_OUT]\n");
				if (tokens->token == HEREDOC)
					printf("[HERE_DOC]\n");
				if (tokens->token == PIPE)
					printf("[PIPE]\n");
				if (tokens->token == ENV)
					printf("[ENV]\n");
				if (tokens->token == QUOTE)
					printf("[QUOTE]\n");
				if (tokens->token == D_QUOTE)
					printf("[D_QUOTE]\n");
				if (tokens->token == BLANK)
					printf("[BLANK]\n");
				if (tokens->token == EXIT_STATUS)
					printf("[EXIT_STATUS]\n");
				tokens = tokens->next;
			}
		}
	}
}
