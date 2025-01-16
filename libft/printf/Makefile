NAME = libftprintf.a

SRC = ft_printf.c ft_print_ptr.c ft_print_num.c \
	 ft_print_hex.c ft_print_unsigned.c ft_putchar.c ft_putstr.c

OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

# hado ghir alwan matsawalnich 3lihom Lol
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
BLUE = \033[0;94m
CYAN = \033[0;96m
######################################

all: $(NAME)

$(NAME):	$(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo "$(GREEN)ft_printf compiled!$(DEF_COLOR)"

clean:
	@$(RM) $(OBJS)
	@echo "$(BLUE)ft_printf object files cleaned!$(DEF_COLOR)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(CYAN)ft_printf executable files cleaned!$(DEF_COLOR)"

re:	fclean all

.PHONY: all fclean clean re
