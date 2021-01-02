#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
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

typedef struct s_setting
{
	char **envp;
	int pipe_fd[2];
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

//execute_commands
int		execute_multi_commands(t_list *cmd, t_setting *setting);
int		execute_command(char **split_by_pipes, t_setting *setting);
int		passing_to_stdout(char **one_cmd_split, t_setting *setting);
int		passing_to_pipe(char **one_cmd_split, t_setting *setting);
int		execve_pipe(int num_cmd, char **argv, t_setting *setting);
int		execve_nopipe(int num_cmd, char **argv, t_setting *setting);
char	*string_tolower(char *str);
int		which_command(char *cmd);

#endif