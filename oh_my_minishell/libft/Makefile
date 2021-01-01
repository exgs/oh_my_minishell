CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = ft_memset.c ft_bzero.c  ft_memcpy.c  ft_memccpy.c  ft_memmove.c  ft_memchr.c  ft_memcmp.c  ft_strlen.c  \
		ft_strlcpy.c  ft_strlcat.c  ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
			ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c \
				 ft_substr.c  ft_strjoin.c  ft_strtrim.c  ft_split.c  ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
				 	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS = ft_memset.o ft_bzero.o  ft_memcpy.o  ft_memccpy.o  ft_memmove.o  ft_memchr.o  ft_memcmp.o  ft_strlen.o  \
		ft_strlcpy.o  ft_strlcat.o  ft_strchr.o ft_strrchr.o ft_strnstr.o ft_strncmp.o ft_atoi.o ft_isalpha.o ft_isdigit.o \
			ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o ft_calloc.o ft_strdup.o \
				 ft_substr.o  ft_strjoin.o  ft_strtrim.o  ft_split.o  ft_itoa.o ft_strmapi.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o

OBJS_ALL = $(SRCS:%.c=%.o)
#OBJS_ALL = $(SRCS: .c=.o) Same
all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

#%.o : %.c 와 같은 식
#$(OBJS_ALL) : $(SRCS)
#	$(CC) $(CFLAGS) -c $(SRCS)
#$(OBJS) : $(SRCS)
#	$(CC) $(CFLAGS) -c $(OBJS:%.o=%.c)


$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
# $(OBJS_ALL) : $(SRCS)와 $(OBJS) : $(SRCS)의 줄 순서를 바꾸면, make all에서 lst 함수까지 컴파일된다.
# 게다가 overwriting이라는 문제도 발생함.
.PHONY: clean bonus re fclean all

bonus : $(NAME) $(OBJS_ALL)
	ar rc $(NAME) $(OBJS_ALL)
	ranlib $(NAME)
clean :
	rm -f $(OBJS_ALL)
fclean : clean
	rm -f $(NAME)
re : fclean all