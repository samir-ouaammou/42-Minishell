#
NAME = pipex

SRCS = pipex.c pipex_utils.c
SRCS_BONUS = pipex_bonus.c pipex_utils_bonus.c pipex_utils_bonus_two.c
SRCS_GET_NEXT = $(PATH_GET_NEXT)/get_next_line.c \
	$(PATH_GET_NEXT)/get_next_line_utils.c

PATH_LIBFT = ../libft
LIBFT = $(PATH_LIBFT)/libft.a
PATH_GET_NEXT = $(PATH_LIBFT)/get_next_line

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJS_GET_NEXT = $(SRCS_GET_NEXT:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_GET_NEXT)
	@make -C $(PATH_LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_GET_NEXT) $(LIBFT) -o $(NAME)

bonus: pipex_bonus

pipex_bonus: $(OBJS_BONUS) $(OBJS_GET_NEXT)
	@make -C $(PATH_LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(OBJS_GET_NEXT) $(LIBFT) -o $(NAME)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_GET_NEXT)
	@make clean -C $(PATH_LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(PATH_LIBFT)

re: fclean all
