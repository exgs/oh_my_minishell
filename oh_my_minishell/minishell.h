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

char	*ft_strsep(char **stringp, const char *delim);
void	del(void *content);
void	print_cmd_list(t_list *cmd);

void free_split(char **argv);
void print_split(char **split);

int commands_execve(t_list *cmd, char **envp);
int command_execve(int i_cmd, char **argv, char **envp);
char *string_tolower(char *str);
void get_cmd_from_gnl(t_list **cmd, char *line);
int which_command(char *cmd);

#endif