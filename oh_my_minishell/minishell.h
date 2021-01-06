#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# define READ 0
# define WRTIE 1
# define FALSE 0
# define TRUE 1

# define ECHO 0
# define CD 1
# define PWD 2
# define EXPORT 3
# define UNSET 4
# define ENV 5
# define EXIT 6
# define LS 7
# define GREP 8

# define READ 0
# define WRITE 1

# define RDONLY 0
# define WRONLY 1
# define RDWR 2

typedef struct	s_data {
	unsigned char	exit_status;
}				t_data;

typedef struct s_setting
{
	char **envp;
	int pipe_fd[2];
	int pipe_fd2[2];
}t_setting;

//get_commands_from_gnl.c
char	*ft_strsep(char **stringp, const char *delim);
void	del(void *content);
char	*string_tolower(char *str);
void	get_commands_from_gnl(t_list **cmd, char *line, t_setting *setting);

//print.c
void	print_cmd_list(t_list *cmd);
void	free_split(char **argv);
void	print_split(char **split);

//execute_commands.c
int		execute_multi_commands(t_list *cmd, t_setting *setting);
int		execute_command(char **split_by_pipes, t_setting *setting);

int		passing_to_stdout(char **one_cmd_split, char *one_cmd_trimed, t_setting *setting);
int		execve_rw_endofpipe(int num_cmd, char **argv, char *one_cmd_trimed, t_setting *setting);
int		execve_w_endofpipe(int num_cmd, char **argv, char *one_cmd_trimed, t_setting *setting);

int		passing_to_pipe(char **one_cmd_split, t_setting *setting);
int		execve_rw_pipe(int num_cmd, char **argv, t_setting *setting);
int		execve_w_pipe(int num_cmd, char **argv, t_setting *setting);

char	*string_tolower(char *str);
int		which_command(char *cmd);
int		which_typeof_command(int num_cmd);
int		flush_pipe_fd(t_setting *setting);

//execute_echo.c
void	execute_echo(char *one_cmd_trimed);

//execute_pwd.c
void execute_pwd(void);

//execute_exit.c
void execute_exit(char **argv);

//utils_jikang.c
t_data	*get_param();
int		ft_is_whitespace(char c);

//1.7_yunslee.c
int	execute_command_nopipe(char *one_cmd, t_setting *setting);

#endif