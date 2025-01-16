NAME =	libft.a

SRC =	ft_strlen.c  ft_memcpy.c ft_strncmp.c ft_isdigit.c \
	ft_split.c ft_putchar_fd.c ft_itoa.c ft_atoi.c ft_strjoin.c \
	ft_putchar_fd.c  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \

OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf
AR = ar -rc
H_LIBFT = libft.h

all:	$(NAME)

$(NAME):  $(OBJS)
	@$(AR) $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
