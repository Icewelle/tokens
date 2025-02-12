MAKEFLAGS += --silent
NAME			= minishell

COMPILER		= cc

FLAGS			= -g3 -Wall -Wextra -Werror

# To use readline and history
LIBS			= -lreadline -lhistory

INCLUDES		= -I ./includes/

SRC_DIR			= ./src/

# Where all .o are stored, the folder structure in bin is the same as src
BIN_DIR			= ./bin/

SRCS_FILE		= main.c \
					signals/signals_handlers.c \
					utils/ft_size/ft_size.c \
					utils/ft_free.c \
					utils/t_token/t_token_utils.c \
					utils/t_token/t_token_utils_2.c \
					utils/builtins/builtins_utils.c \
					utils/exec/token_management.c \
					utils/exec/path_finding.c \
					utils/t_processus/t_processus_utils.c \
					utils/t_processus/t_processus_utils_2.c \
					utils/t_envp/t_envp_utils.c \
					utils/t_envp/t_envp_utils_2.c \
					utils/t_envp/t_envp_utils_3.c \
					utils/ft_error.c \
					builtins/builtins_exec.c \
					builtins/echo.c \
					builtins/pwd.c \
					builtins/cd.c \
					builtins/env.c \
					builtins/unset.c \
					builtins/export.c \
					builtins/exit.c \
					exec/command_line_exec.c \
					exec/processus_management.c \
					exec/tokens/heredoc.c \
					exec/tokens/redir.c \
					tokenization/create_tokens.c\
					tokenization/put_env.c

# Convert .c files to .o files
SRCS_COMPILE	= $(SRCS_FILE:.c=.o)

# Convert source paths to object paths, replacing src with bin
SRCS_COMPILE_PATH = $(addprefix $(BIN_DIR), $(patsubst %, %, $(SRCS_COMPILE)))

MAKE_LIBFT		= $(MAKE) -C ./src/utils/libft -s

LIBFT			= ./src/utils/libft/libft.a

MAKE_GARBAGE	= $(MAKE) -C ./src/utils/garbage_collector -s

GARBAGE			= ./src/utils/garbage_collector/garbage_collector.a

# Colors
NC				= \033[0m

YELLOW			= \033[38;5;208m
PURPLE			= \033[38;5;212m

YELLOW_UNDERLINE = \033[4;38;5;208m
PURPLE_UNDERLINE = \033[4;38;5;212m

# Show how many files are compilated for the libft and minishell, also show how many headers are included
COMPILE_MSG = "\
\n$(PURPLE_UNDERLINE)Minishell compilation:$(NC)$(PURPLE)\n\
\tLibft: $$(find ./src/utils/libft -name '*.c' | wc -l) file(s) compiled.\n\
\tMinishell: $$(expr $$(find ./src -path ./src/utils/libft -prune -o -name '*.c' | wc -l) - 1) file(s) compiled.\n\
\tHeaders: $$(find ./includes -name '*.h' | wc -l) file(s) included.\n\n\
$$(find . -name '*.a' -exec printf "\t%s created.\n" {} \;)\n\
\t./$(NAME) created.\
\n$(NC)"

# Show the total of .o deleted
CLEAN_MSG = "\
\n$(YELLOW_UNDERLINE)Cleaning information:$(NC)$(YELLOW)\n\
\t$$(find ./bin -name '*.o' | wc -l) file(s) deleted.\
$(NC)"

# Show minishell and .a delete text
FCLEAN_MSG = "\
\n$(YELLOW)\
$$(find . -name '*.a' -exec printf "\t%s removed." {} \;)\n\
$$(find . -name $(NAME) -exec printf "\t%s removed." {} \;)\n\
$(NC)"

# Check if dir exist before compiling files
$(BIN_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(COMPILER) $(FLAGS) -c $< -o $@ $(INCLUDES)

# Create program executable
$(NAME): $(SRCS_COMPILE_PATH)
	@$(MAKE_LIBFT)
	@$(MAKE_GARBAGE)
	@$(COMPILER) $(FLAGS) -o $(NAME) $(SRCS_COMPILE_PATH) $(INCLUDES) $(LIBS) $(LIBFT) $(GARBAGE)
	@echo $(COMPILE_MSG)

# Default rule: make
all: $(NAME)

# Call echo, remove the bin directory and all .o from the root folder in case a file has been lost somewhere
clean:
	@echo $(CLEAN_MSG)
	@/bin/rm -rf $(BIN_DIR)
	@find . -name '*.o' -delete
	@$(MAKE_LIBFT) -s clean
	@$(MAKE_GARBAGE) -s clean

# Make a clean before removing minishell and .a files, call echo, make fclean on libft
fclean:
	@$(MAKE) -s clean
	@echo $(FCLEAN_MSG)
	@/bin/rm -f $(NAME)
	@$(MAKE_LIBFT) -s fclean
	@$(MAKE_GARBAGE) -s fclean

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re
