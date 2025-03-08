NAME =	libft.a

SRC =	ft_strlen.c	ft_memcpy.c	ft_strcmp.c	ft_isdigit.c	ft_strlcpy.c	ft_strrchr.c \
	ft_split.c	ft_putchar_fd.c	ft_itoa.c	ft_atoi.c	ft_strjoin.c	ft_strdup.c  \
	ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c	ft_strncmp.c	ft_strchr.c \
	ft_substr.c	ft_strcpy.c	ft_lstnew.c	ft_lstadd_back.c	ft_strncpy.c	ft_isalpha.c

OBJS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

AR = ar -rc

H_LIBFT = libft.h

all:	$(NAME)

$(NAME):  $(OBJS)
	@$(AR) $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
