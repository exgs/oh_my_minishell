SRCS		=	gnl/get_next_line.c\
				gnl/get_next_line_utils.c\
				main.c\
				execute_commands.c\
				get_commands_from_gnl.c\
				print_free.c\
				utils_a.c\
				utils_b.c\
				pipe.c\
				signal.c\
				vector.c\
				refine_line_a.c\
				refine_line_b.c\
				refine_line_c.c\
				refine_line_d.c\
				check_command.c\
				execute_echo.c\
				execute_pwd.c\
				execute_exit.c\
				execute_env.c\
				execute_unset.c\
				execute_export_a.c\
				execute_export_b.c\
				execute_cd.c\
				execute_path.c\
				is_execve.c\
				redirection.c\
				ft_strsemi.c\
				msg_error.c\
				split_pipe.c\
				unseal_firstquotes.c\
				check_command_utils.c\
				pipe_utils.c\
				redirection_execute_part.c\
				execute_path_utils.c\
				execute_cd_utils.c\
				redirection_utils.c\
				init.c\
				exit.c\
				ft_split_minishell.c\
				ft_split_minishell_utils.c\
				check_semicolon.c
				
NAME		=	minishell
LIBFT		=	libft
RM			=	rm -f
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

$(NAME) :	$(SRCS)
			$(MAKE) bonus -C $(LIBFT)/
			$(CC) $(CFLAGS) $(LIBFT)/$(LIBFT).a $^ -o $@

fsan	:
			$(CC) -fsanitize=address -g libft/*.c gnl/*.c *.c -o minishell

all		:	$(NAME)

clean	:
			$(MAKE) clean -C $(LIBFT)/

fclean	:	clean
			$(RM) $(LIBFT)/$(LIBFT).a
			$(RM) $(NAME)

debug	:
			$(CC) $(CFLAGS) libft/*.c gnl/*.c *.c -o minishell -g

re		:	fclean all

.PHONY	:	all clean fclean re