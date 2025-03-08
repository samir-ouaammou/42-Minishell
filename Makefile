# SRCS_MAIN
SRCS_MAIN   = minishell.c

# SRCS_PARSING
SRCS_PARSING =  $(PATH_PARSING)/main_parsing.c \
                $(PATH_PARSING)/main_parsing_utils.c \
                $(PATH_PARSING)/input_splitter.c \
                $(PATH_PARSING)/input_splitter_utils.c \
                $(PATH_PARSING)/input_validator.c \
                $(PATH_PARSING)/input_validator_utils.c \
                $(PATH_PARSING)/pars_redirections.c \
                $(PATH_PARSING)/pars_redirections_utils.c \
                $(PATH_PARSING)/create_list.c \
                $(PATH_PARSING)/create_list_utils.c \
                $(PATH_PARSING)/create_ast_tree.c \
                $(PATH_PARSING)/create_ast_tree_utils.c \
                $(PATH_PARSING)/remove_qouts.c \
                $(PATH_PARSING)/remove_qouts_utils.c \
                $(PATH_PARSING)/here_doc.c \
                $(PATH_PARSING)/here_doc_utils.c \
                $(PATH_PARSING)/here_doc_utils1.c \
                $(PATH_PARSING)/here_doc_utils2.c 

# SRCS_EXACTION
SRCS_EXACTION = $(PATH_EXACTION)/exaction.c \
                $(PATH_EXACTION)/exaction_utils.c \
                $(PATH_EXACTION)/is_operator.c \
                $(PATH_EXACTION)/env_path.c \
                $(PATH_EXACTION)/command_execution.c \
                $(PATH_EXACTION)/command_execution_utils.c \
                $(PATH_EXACTION)/execution_pipes.c \
                $(PATH_EXACTION)/wildcard_expansion.c \
                $(PATH_EXACTION)/redirection.c \
                $(PATH_EXACTION)/redirection_utils.c \
                $(PATH_EXACTION)/execution_handler_ast.c \
                $(PATH_EXACTION)/env_handler.c \
                $(PATH_EXACTION)/env_handler_utils.c \
                $(PATH_EXACTION)/process_variables.c \
                $(PATH_EXACTION)/execution_handler_ast_utils.c \
                $(PATH_EXACTION)/process_variables_utils.c \
                $(PATH_EXACTION)/process_variables_utils2.c \
                $(PATH_EXACTION)/handle_heredoc.c \

# SRCS_BUILTINS
SRCS_BUILTINS = $(PATH_BUILTINS)/builtin_echo.c \
                $(PATH_BUILTINS)/builtin_env.c  \
                $(PATH_BUILTINS)/builtin_cd.c\
                $(PATH_BUILTINS)/builtin_exit.c \
                $(PATH_BUILTINS)/builtin_export.c \
                $(PATH_BUILTINS)/builtin_export_utils.c \
                $(PATH_BUILTINS)/builtin_export_utils2.c \
                $(PATH_BUILTINS)/builtin_export_utils3.c \
                $(PATH_BUILTINS)/builtin_export_utils4.c \
                $(PATH_BUILTINS)/builtin_pwd.c \
                $(PATH_BUILTINS)/builtin_unset.c \
                $(PATH_BUILTINS)/builtin_unset_utils.c

# SRCS_MALLOC
SRCS_MALLOC = $(PATH_MALLOC)/malloc.c \
              $(PATH_MALLOC)/malloc_utils.c

# SRCS_WILDCARDS
SRCS_WILDCARDS = $(PATH_WILDCARDS)/wildcard.c

# SRCS_SIGNALS
SRCS_SIGNALS = $(PATH_SIGNALS)/signals.c

# PROGRAM NAME
NAME = minishell

PATH_MALLOC = ./malloc
PATH_PARSING = ./parsing
PATH_SIGNALS = ./signals
PATH_EXACTION = ./exaction
PATH_BUILTINS = ./builtins
PATH_WILDCARDS = ./wildcards

# OBJS: Object files
OBJS_MAIN = $(SRCS_MAIN:.c=.o)
OBJS_MALLOC = $(SRCS_MALLOC:.c=.o)
OBJS_SIGNALS = $(SRCS_SIGNALS:.c=.o)
OBJS_PARSING = $(SRCS_PARSING:.c=.o)
OBJS_EXACTION = $(SRCS_EXACTION:.c=.o)
OBJS_BUILTINS = $(SRCS_BUILTINS:.c=.o)
OBJS_WILDCARDS = $(SRCS_WILDCARDS:.c=.o)

# LIBFT: Paths
LIBFT_PATH = ./libft
LIBFT_AR = $(LIBFT_PATH)/libft.a

# PRINTF: Paths
PRINTF_PATH = $(LIBFT_PATH)/printf
PRINTF_AR = $(PRINTF_PATH)/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-g3  -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS_MAIN) $(OBJS_MALLOC) $(OBJS_PARSING) $(OBJS_EXACTION) $(OBJS_BUILTINS) $(OBJS_SIGNALS) $(OBJS_WILDCARDS)
	@make --no-print-directory -C $(LIBFT_PATH)
	@make --no-print-directory -C $(PRINTF_PATH)
	@$(CC) $(CFLAGS) $(OBJS_MAIN) $(OBJS_MALLOC) $(OBJS_PARSING) $(OBJS_EXACTION) $(OBJS_BUILTINS) $(OBJS_SIGNALS) $(OBJS_WILDCARDS) $(LIBFT_AR) $(PRINTF_AR) -o $(NAME) -lreadline
	@echo "\033[1;32m✅ Compilation finished successfully!\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean --no-print-directory -C $(LIBFT_PATH)
	@make clean --no-print-directory -C $(PRINTF_PATH)
	@find . -name "*.o" -delete
	@echo "\033[1;34m🧹 Clean completed.\033[0m"

fclean: clean
	@make fclean --no-print-directory -C $(LIBFT_PATH)
	@make fclean --no-print-directory -C $(PRINTF_PATH)
	@rm -f $(NAME)
	@echo "\033[1;31m🗑️ Full clean completed.\033[0m"


re: fclean all

.PHONY: all bonus clean fclean
