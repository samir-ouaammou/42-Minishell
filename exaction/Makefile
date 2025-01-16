NAME = minishell

SRCS = main.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT_PATH = ./libft
LIBFT_AR = ./libft/libft.a

PRINTF_PATH = ./libft/printf
PRINTF_AR = ./libft/printf/libftprintf.a

PIPEX_PATH = ./pipex
PIPEX_PRO = ./pipex/pipex

all:	$(NAME)

$(NAME):	$(OBJS)
	@make -C $(LIBFT_PATH)
	@make -C $(PRINTF_PATH)
	@make -C $(PIPEX_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_AR) $(PRINTF_AR) $(PIPEX_PRO) -o $(NAME) -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(PRINTF_PATH)
	@make clean -C $(PIPEX_PATH)
	@rm -r $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(PRINTF_PATH)
	@make fclean -C $(PIPEX_PATH)
	@rm -r $(NAME)