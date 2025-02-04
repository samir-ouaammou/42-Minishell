NAME = minishell

SRCS_EXACTION = minishell.c $(PATH_EXACTION)/exaction.c $(PATH_EXACTION)/builtins/echo.c $(PATH_EXACTION)/builtins/env.c $(PATH_EXACTION)/builtins/exit.c \
	$(PATH_EXACTION)/builtins/export.c $(PATH_EXACTION)/builtins/pwd.c $(PATH_EXACTION)/builtins/unset.c
SRCS_PARSING = $(PATH_PARSING)/1_main_parsing.c $(PATH_PARSING)/2_input_splitter_utils.c $(PATH_PARSING)/2_input_splitter.c \
	$(PATH_PARSING)/3_input_validator_utils.c $(PATH_PARSING)/3_input_validator.c $(PATH_PARSING)/4_creat_ast_three_utils.c \
	$(PATH_PARSING)/4_creat_ast_three.c $(PATH_PARSING)/5_free_parsing.c $(GET_NEXT_PATH)/get_next_line_utils.c $(GET_NEXT_PATH)/get_next_line.c

OBJS_EXACTION = $(SRCS_EXACTION:.c=.o)
OBJS_PARSING = $(SRCS_PARSING:.c=.o)

# PATH EXACTION
PATH_EXACTION = ./exaction

# PATH PARSING
PATH_PARSING = ./parsing

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

# PATH LIBFT
LIBFT_PATH = ./libft
LIBFT_AR = $(LIBFT_PATH)/libft.a

# PATH PRINTF
PRINTF_PATH = $(LIBFT_PATH)/printf
PRINTF_AR = $(PRINTF_PATH)/libftprintf.a

# PATH PRINTF
GET_NEXT_PATH = $(LIBFT_PATH)/get_next_line

all:	$(NAME)

$(NAME):	$(OBJS_EXACTION) $(OBJS_PARSING)
	@make -C $(LIBFT_PATH)
	@make -C $(PRINTF_PATH)
	$(CC) $(CFLAGS) $(OBJS_EXACTION) $(OBJS_PARSING) $(LIBFT_AR) $(PRINTF_AR) -o $(NAME) -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(PRINTF_PATH)
	@rm -r $(OBJS_EXACTION) $(OBJS_PARSING)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(PRINTF_PATH)
	@rm -r $(NAME)

re: fclean all