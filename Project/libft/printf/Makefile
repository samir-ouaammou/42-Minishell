NAME = libftprintf.a

SRC = ft_printf.c ft_print_ptr.c ft_print_num.c \
		ft_print_hex.c	ft_print_unsigned.c	ft_putchar.c	ft_putstr.c

OBJS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

$(NAME):	$(OBJS)
	@ar rc $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all fclean clean re

