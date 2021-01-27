/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:09:05 by jikang            #+#    #+#             */
/*   Updated: 2021/01/27 19:59:10 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"

# define ERROR		-1
# define FALSE		0
# define TRUE		1

/*
** CMD NUM
*/

# define ECHO		0
# define LS			1
# define GREP		2
# define CLEAR		3
# define CAT		4

/*
** PIPE
*/

# define READ		0
# define WRITE		1

/*
** BUFF
*/

# define BUFF_MAX	1000

enum				e_except
{
	NONE,
	SYNTAX,
	EX_END
};

enum				e_flag
{
	CTRL_D,
	CTRL_C,
	CTRL_BS,
	F_END
};

enum				e_redirect
{
	LEFT = 1,
	RIGHT,
	D_RIGHT,
	R_END
};

int					g_flag[F_END];
char				g_except[EX_END];
int					g_status;
char				g_buf[1000];
int					g_dup_stdin;
int					g_dup_stdout;

typedef struct		s_var
{
	int				i;
	int				k;
	int				l;
	int				flag_bq;
	int				flag_sq;
	int				flag_backslash;
	int				flag_pipe;
}					t_var;

typedef struct		s_data
{
	char			**cmd_splited;
	char			*cmd_trimed;
	char			***cmd_redirect;
	char			*symbol_array;
	char			**envp;
	int				semi_arr[BUFF_MAX];
}					t_data;

typedef struct		s_index
{
	int				i;
	int				j;
	int				z;
	int				before;
	int				cnt;
	int				redir_num;
	unsigned char	f_quote;
}					t_index;

typedef int	(*t_builtin)(const char *, char *const[], char *const[]);

/*
**	get_commands_from_gnl.c
*/

void				del(void *content);
char				*string_tolower(char *str);
void				get_commands_from_gnl(t_list **cmd, char *line);

/*
**	print_free.c
*/

void				print_cmd_list(t_list *cmd);
void				free_split(char **argv);
void				print_split(char **split);
void				free_3d_split(char ***argv);
void				print_3d_split(char ***argv);

/*
**	execute_commands.c
*/

int					execute_multi_commands(t_list *cmd);
int					execute_command(char **split_by_pipes);

/*
**	execute_echo.c
*/

int					execute_echo(const char *path, char *const argv[],
									char *const envp[]);

/*
**	execute_pwd.c
*/

int					execute_pwd(const char *path, char *const argv[],
									char *const envp[]);

/*
**	execute_exit.c
*/
int					execute_exit(const char *path, char *const argv[],
									char *const envp[]);

/*
**	utils_a.c
*/

t_data				*get_param();
int					ft_is_whitespace(char c);
void				init_array(char *buff);
void				init_array_int(int *buff);
void				change_flag(int *flag);

/*
**	utils_b.c
*/

void				check_semicolon(char *str);
char				*ft_strdup_by_index(char *str, int start, int end);
void				free_init(char **data, char *init);
void				init_value(char *buff, t_var *v);

/*
**	pipe.c
*/
int					execute_command_nopipe(char *one_cmd);
int					execute_command_pipe(char **split_by_pipes,
											int *fd, int i);

/*
**	pipe_utils.c
*/

char				*string_tolower(char *str);
int					which_command(char *cmd);
int					need_redirection(void);

/*
**	char	*which_command2(int num_cmd);
*/

void				parent_process(char **split_by_pipes, int *fd, int i);
void				child_process(char **one_cmd_splited, int *fd);
int					need_redirection();

/*
**	signal.c
*/
void				catch_signals(void);

/*
** init.c
*/

void				minishell_init(int argc, char *argv[], char **envp);
void				dup_initalize();

/*
**	 exit.c
*/

void				minishell_exit(t_list *cmds);
void				cmds_exit(t_list *cmd);
void				cmd_exit();

/*
**	 vector.c
*/

void				vector_sort(char *arr[]);
int					vector_size(char *arr[]);
void				vector_clear(char *arr[]);
char				**vector_dup(char *arr[]);
void				vector_push_back(char **arr[], char str[]);

int					execute_env(const char *path, char *const argv[],
									char *const envp[]);
int					execute_unset(const char *path, char *const argv[],
									char *const envp[]);
int					execute_export(const char *path, char *const argv[],
									char *const envp[]);
void				print_envp(char **envp);
int					execute_cd(const char *path, char *const argv[],
									char *const envp[]);
int					execute_path(const char *path, char *const argv[],
									char *const envp[]);

/*
**	execute_cd_utils.c
*/

int					is_home_cd(const char *str);

/*
**	execute_path_utils.c
*/

int					command_not_found_g_status(char *str);
void				copy_pathname(char *str, char *buff);
int					is_macro_in_envp(const char *env_line, char *buff);

/*
**	check_command.c
*/

void				check_command(char *cmd, char *argv[], char *envp[]);

/*
**	check_command_utils.c
*/

char				*get_path(char *cmd, char *argv[], char *envp[]);
void				ft_execve(const char *path, char *const argv[],
										char *const envp[]);

/*
**	is_execve.c
*/

int					is_execve(char *path, char **cmd_split, char *envp[]);

/*
**	redirection.c
*/

char				***splited_by_redirect(char **one_cmd_splited,
											char **array);
int					parsing_redirect(char *str);

/*
**	redirection_execute_part.c
*/

int					execute_nopipe_redirect();

/*
**	redirection_utils.c
*/

void				input_symbol(char **split, char *symbol_array,
												t_index *index);
int					parsing_redirect(char *str);
void				s_index_bzero(t_index *index);

/*
**	ft_strsemi.c
*/

char				*ft_strsemi(char **str, int *array, int i);

/*
**	refine_line_a.c
*/

char				*refine_line(char *line);

/*
**	refine_line_b.c
*/

int					refining_factory(char *buff, char *line,
										t_var *v, char **envlist);

/*
**	refine_line_c.c
*/

int					convert_env(char *buff, char *line,
										t_var *v, char **envlist);

/*
**	refine_line_d.c
*/

int					replace_env(char *temp, char **envlist);

/*
**	split_pipe.c
*/

char				**split_pipe(char *substr);
void				unseal_firstquotes(char **splited);

/*
**	msg_error.c
*/

int					msg_error(char *program, char *cmd,
								char *arg, int exit_status);
int					msg_invalid(char *program, char *cmd,
								char *arg, int exit_status);

/*
**	unseal_firstquotes.c
*/

void				unseal_firstquotes(char **splited);

/*
**	ft_split_minishell.c
*/

char				**ft_split_minishell(char const *s, char c);

/*
**	execute_unset.c
*/

void				change_argv(char **argv);
#endif
