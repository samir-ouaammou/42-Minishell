# SRCS_MAIN
SRCS_MAIN   = minishell.c

# SRCS_PARSING
SRCS_PARSING =  $(PATH_PARSING)/1_main_parsing.c \
                $(PATH_PARSING)/2_input_splitter_utils.c \
                $(PATH_PARSING)/2_input_splitter.c  \
                $(PATH_PARSING)/3_input_validator_utils.c \
                $(PATH_PARSING)/3_input_validator.c \
                $(PATH_PARSING)/4_pars_redirections.c \
                $(PATH_PARSING)/5_creat_ast_tree_utils.c \
                $(PATH_PARSING)/5_creat_ast_tree.c \
                $(PATH_PARSING)/6_free_parsing.c \
                $(PATH_PARSING)/7_remove_qouts.c \
                $(PATH_PARSING)/8_here_doc.c \
                $(PATH_PARSING)/9_handle_wildcard.c  \
                $(GET_NEXT_PATH)/get_next_line_utils.c \
                $(GET_NEXT_PATH)/get_next_line.c

# SRCS_EXACTION
SRCS_EXACTION = $(PATH_EXACTION)/exaction.c \
                $(PATH_EXACTION)/is_operator.c \
                $(PATH_EXACTION)/env_path.c \
                $(PATH_EXACTION)/command_execution.c \
                $(PATH_EXACTION)/execution_pipes.c \
                $(PATH_EXACTION)/wildcard_expansion.c \
                $(PATH_EXACTION)/output_redirection.c \
                $(PATH_EXACTION)/input_redirection.c \
                $(PATH_EXACTION)/execution_handler_ast.c \
                $(PATH_EXACTION)/env_handler.c \
                $(PATH_EXACTION)/process_variables.c \
                $(PATH_EXACTION)/execution_handler_ast_utils.c \
                $(PATH_EXACTION)/process_variables_utils.c \
                $(PATH_EXACTION)/input_redirection_utils.c \
                $(PATH_EXACTION)/handle_heredoc.c \
		$(PATH_EXACTION)/memory_cleanup.c

# SRCS_BUILTINS
SRCS_BUILTINS = $(PATH_BUILTINS)/builtin_echo.c \
                $(PATH_BUILTINS)/builtin_env.c  \
                $(PATH_BUILTINS)/builtin_cd.c\
                $(PATH_BUILTINS)/builtin_exit.c \
                $(PATH_BUILTINS)/builtin_export.c \
                $(PATH_BUILTINS)/builtin_pwd.c \
                $(PATH_BUILTINS)/builtin_unset.c

NAME = minishell

PATH_PARSING = ./parsing
PATH_EXACTION = ./exaction
PATH_BUILTINS = ./builtins

# OBJS: Object files
OBJS_MAIN = $(SRCS_MAIN:.c=.o)
OBJS_PARSING = $(SRCS_PARSING:.c=.o)
OBJS_EXACTION = $(SRCS_EXACTION:.c=.o)
OBJS_BUILTINS = $(SRCS_BUILTINS:.c=.o)

# LIBFT: Paths
LIBFT_PATH = ./libft
LIBFT_AR = $(LIBFT_PATH)/libft.a

# PRINTF: Paths
PRINTF_PATH = $(LIBFT_PATH)/printf
PRINTF_AR = $(PRINTF_PATH)/libftprintf.a

# GET_NEXT: Path
GET_NEXT_PATH = $(LIBFT_PATH)/get_next_line


CC = cc
CFLAGS = -Wall -Wextra -Werror  -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS_MAIN) $(OBJS_PARSING) $(OBJS_EXACTION) $(OBJS_BUILTINS)
	@make -C $(LIBFT_PATH)
	@make -C $(PRINTF_PATH)
	@$(CC) $(CFLAGS) $(OBJS_MAIN) $(OBJS_PARSING) $(OBJS_EXACTION) $(OBJS_BUILTINS) $(LIBFT_AR) $(PRINTF_AR) -o $(NAME) -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(PRINTF_PATH)
	@rm -r $(OBJS_MAIN) $(OBJS_PARSING) $(OBJS_EXACTION) $(OBJS_BUILTINS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(PRINTF_PATH)
	@rm -r $(NAME)

re: fclean all