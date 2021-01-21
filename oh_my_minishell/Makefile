UTILS		= ./libft/ft_memset.c ./libft/ft_bzero.c  ./libft/ft_memcpy.c  ./libft/ft_memccpy.c  ./libft/ft_memmove.c  ./libft/ft_memchr.c  ./libft/ft_memcmp.c  ./libft/ft_strlen.c  \
				./libft/ft_strlcpy.c  ./libft/ft_strlcat.c  ./libft/ft_strchr.c ./libft/ft_strrchr.c ./libft/ft_strnstr.c ./libft/ft_strncmp.c ./libft/ft_atoi.c ./libft/ft_isalpha.c ./libft/ft_isdigit.c \
					./libft/ft_isalnum.c ./libft/ft_isascii.c ./libft/ft_isprint.c ./libft/ft_toupper.c ./libft/ft_tolower.c ./libft/ft_calloc.c ./libft/ft_strdup.c \
				 		./libft/ft_substr.c  ./libft/ft_strjoin.c  ./libft/ft_strtrim.c  ./libft/ft_split.c  ./libft/ft_itoa.c ./libft/ft_strmapi.c ./libft/ft_putchar_fd.c ./libft/ft_putstr_fd.c ./libft/ft_putendl_fd.c ./libft/ft_putnbr_fd.c\
				 			./libft/ft_lstnew.c ./libft/ft_lstadd_front.c ./libft/ft_lstsize.c ./libft/ft_lstlast.c ./libft/ft_lstadd_back.c ./libft/ft_lstdelone.c ./libft/ft_lstclear.c ./libft/ft_lstiter.c ./libft/ft_lstmap.c\
								./gnl/get_next_line.c ./gnl/get_next_line_utils.c
SRCS		= main.c execute_commands.c get_commands_from_gnl.c print_free.c utils_a.c utils_b.c pipe.c signal.c vector.c refine_line_a.c refine_line_b.c refine_line_c.c refine_line_d.c\
				check_command.c execute_echo.c execute_pwd.c execute_exit.c execute_env.c execute_unset.c execute_export_a.c execute_export_b.c execute_cd.c execute_path.c \
					is_execve.c redirection.c ft_strsemi.c msg_error.c split_pipe.c unseal_firstquotes.c check_command_utils.c pipe_utils.c redirection_execute_part.c execute_path_utils.c execute_cd_utils.c redirection_utils.c \
						init.c exit.c
OBJS		= $(SRCS:.c=.o)
OBJS_UTILS	= $(UTILS:.c=.o)
CC			= gcc
CFLAG		= -Wall -Wextra -Werror -g3 -fsanitize=address

# ./libft/libft.a :
# 	$(MAKE) -C ./libft all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(LIBRARY)
	$(CC) $(CFLAG) $(OBJS) -lft_gnl -L.
$(LIBRARY)	: $(OBJS_UTILS)
	ar rc $(LIBRARY) $(OBJS_UTILS)
	ranlib $(LIBRARY)

debug :
	gcc -Wall -Wextra -Werror -g ./gnl/*.c ./libft/*.c \
		$(SRCS)
fsan :
	gcc -g3 -fsanitize=address ./gnl/*.c ./libft/*.c \
		$(SRCS)
all	: $(NAME)
clean :
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(OBJS_UTILS)
	rm -rf ./libft/libft.a
	rm -rf ./libft_gnl.a
	rm -rf $(OBJS) a.out
re	 : clean all
.PHONY : all clean fclean re