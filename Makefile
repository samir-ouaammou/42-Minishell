# Directories for parsing, execution, and builtins
PATH_PARSING = ./parsing
PATH_EXACTION = ./exaction
PATH_BUILTINS = ./builtins

# SRCS_PARSING
SRCS_PARSING = $(PATH_PARSING)/1_main_parsing.c \
               $(PATH_PARSING)/2_input_splitter_utils.c \
               $(PATH_PARSING)/2_input_splitter.c  \
               $(PATH_PARSING)/3_input_validator_utils.c \
               $(PATH_PARSING)/3_input_validator.c \
               $(PATH_PARSING)/4_creat_ast_tree_utils.c \
               $(PATH_PARSING)/4_creat_ast_tree.c \
               $(PATH_PARSING)/5_free_parsing.c \
               $(PATH_PARSING)/6_remove_qouts.c \
               $(PATH_PARSING)/7_here_doc.c \
               $(PATH_PARSING)/8_handle_wildcard.c  \
               $(GET_NEXT_PATH)/get_next_line_utils.c \
               $(GET_NEXT_PATH)/get_next_line.c

# SRCS_EXACTION
SRCS_EXACTION = minishell.c $(PATH_EXACTION)/exaction.c

# SRCS_BUILTINS
SRCS_BUILTINS = $(PATH_BUILTINS)/builtin_echo.c \
                $(PATH_BUILTINS)/builtin_env.c  \
                $(PATH_BUILTINS)/builtin_cd.c\
                $(PATH_BUILTINS)/builtin_exit.c \
                $(PATH_BUILTINS)/builtin_export.c \
                $(PATH_BUILTINS)/builtin_pwd.c \
                $(PATH_BUILTINS)/builtin_unset.c

# OBJS: Object files
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


# Final executable name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror # -g3 -fsanitize=address

# Default target
all: $(NAME)

# Build the final executable (minishell)
$(NAME): $(OBJS_PARSING) $(OBJS_EXACTION) $(OBJS_BUILTINS)
	# Build libft and libftprintf libraries first
	@make -C $(LIBFT_PATH)
	@make -C $(PRINTF_PATH)
	# Link object files and libraries to create the executable
	$(CC) $(CFLAGS) $(OBJS_PARSING) $(OBJS_EXACTION) $(OBJS_BUILTINS) $(LIBFT_AR) $(PRINTF_AR) -o $(NAME) -lreadline

# Clean: Remove object files
clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(PRINTF_PATH)
	@rm -r $(OBJS_PARSING) $(OBJS_EXACTION) $(OBJS_BUILTINS)

# Fclean: Remove object files and the final executable
fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(PRINTF_PATH)
	@rm -r $(NAME)

# Rebuild: Clean and then build the program again
re: fclean all
