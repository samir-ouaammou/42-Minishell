NAME = test

SRCS = exaction.c builtins/exit.c builtins/pwd.c builtins/echo.c builtins/unset.c builtins/export.c
SRCS_PIPEX = ./pipex/pipex.c ./pipex/pipex_utils.c

OBJS = $(SRCS:.c=.o)
OBJS_PIPEX = $(SRCS_PIPEX:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

LIBFT_PATH = ../libft
LIBFT_AR = $(LIBFT_PATH)/libft.a

PRINTF_PATH = $(LIBFT_PATH)/printf
PRINTF_AR = $(LIBFT_PATH)/printf/libftprintf.a

PIPEX_PATH = ./pipex

all:	$(NAME)

$(NAME):	$(OBJS) $(OBJS_PIPEX)
	@make -C $(LIBFT_PATH)
	@make -C $(PRINTF_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_PIPEX) $(LIBFT_AR) $(PRINTF_AR) -o $(NAME) -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(PRINTF_PATH)
	@rm -r $(OBJS)
	@rm -r $(OBJS_PIPEX)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(PRINTF_PATH)
	@rm -r $(NAME)

re: fclean all



#cd - && cd ../file or dir && cd ~/yghj