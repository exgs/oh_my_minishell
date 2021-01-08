#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
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
# define DQMARK 9

# define READ 0
# define WRITE 1

# define RDONLY 0
# define WRONLY 1
# define RDWR 2

enum	e_quotes
{
	Q_E = -3,
	Q_B,
	Q_S,
	OUT,
	DQ_S,
	DQ_B,
	DQ_E
};

enum	e_except
{
	NONE,
	SYNTAX,
	EX_END
};

enum	e_flag
{
	CTRL_D,
	CTRL_BS,
	F_END
};


int	g_flag[F_END];
int g_status; // 이걸 256으로 나누면 exit status
typedef struct	s_data {
	// unsigned char	exit_status;
	char **cmd_splited;
	char *cmd_trimed;
	char **envp;
}				t_data;

//get_commands_from_gnl.c
char	*ft_strsep(char **stringp, const char *delim);
void	del(void *content);
char	*string_tolower(char *str);
void	get_commands_from_gnl(t_list **cmd, char *line);

//print.c
void	print_cmd_list(t_list *cmd);
void	free_split(char **argv);
void	print_split(char **split);

//execute_commands.c
int		execute_multi_commands(t_list *cmd);
int		execute_command(char **split_by_pipes);

//execute_echo.c
void	execute_echo(char *one_cmd_trimed);

//execute_pwd.c
void execute_pwd(void);

//execute_exit.c
void execute_exit(char **argv);

//utils_jikang.c
t_data	*get_param();
int		ft_is_whitespace(char c);

//pipe.c
int		execute_command_nopipe(char *one_cmd);
int		execute_command_pipe(char **split_by_pipes, int *fd, int i);
char	*string_tolower(char *str);
int		which_command(char *cmd);
char	*which_command2(int num_cmd);
int		execve_nopipe(int num_cmd, char **argv, char *one_cmd_trimed);
void	parent_process(char **split_by_pipes, int *fd, int i);
void	child_process(char **one_cmd_splited, int *fd);

// signal.c
void	catch_signals(void);
// init_exit.c
void	minishell_init(int argc, char *argv[], char **envp);
void	minishell_exit(t_list *cmds);
void	gnl_exit(t_list *cmds);
void	cmds_exit(t_list *cmd);
void	cmd_exit();

// vector.c
void	vector_erase(char *arr[], int target);
void	vector_sort(char *arr[]);
int		vector_size(char *arr[]);
void	vector_clear(char *arr[]);
char	**vector_dup(char *arr[]);
void	vector_push_back(char **arr[], char str[]);

int		execute_env(const char *path, char *const argv[], char *const envp[]);
int		execute_unset(const char *path, char *const argv[], char *const envp[]);
int		execute_export(const char *path, char *const argv[], char *const envp[]);
int		execute_cd(const char *path, char *const argv[], char *const envp[]);
#endif