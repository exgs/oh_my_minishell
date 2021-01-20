#include "minishell.h"

static char	*get_path(char *cmd, char *argv[], char *envp[])
{
	struct stat	buf;
	char		**arr;
	char		*path;
	char		*tmp;
	int			i;

	while (*envp && ft_strncmp(*envp, "PATH", 5) != '=') // unset PATH 생각해보기
		envp++;
	if (ft_strchr(cmd, '/') || !*envp || !ft_strchr(*envp, '='))
		return (ft_strdup(cmd));
	arr = ft_split(ft_strchr(*envp, '=') + 1, ':'); // unset PATH 일때 터짐 나중에 수정해야함
	i = 0;
	while (arr[i])
	{
		tmp = ft_strjoin("/", cmd);
		path = ft_strjoin(arr[i], tmp);
		free(tmp);
		if (stat(path, &buf) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	vector_clear(arr);
	return (path);
}

int execute_dqmark(const char *path, char *const argv[], char *const envp[])
{
	int i;	int j;
	char **envlist;
	char buff[BUFF_MAX];
	char *str;

	str = get_param()->cmd_trimed;
	envlist = get_param()->envp;
	/* question mark 가 있으면? */
	i = 0;
	if (path[1] == '?')
	{
		ft_putendl_fd(str, 2);
		ft_putstr_fd("minishell: ", 2);
		ft_putnbr_fd(g_status / 256, 2);
		ft_putendl_fd(": command not found", 2);
		g_status = 127 * 256;
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		init_array(buff);
		i = 1;
		while (str[i] != '\0' && str[i] != ' ')
		{
			buff[i - 1] = str[i];
			i++;
		}
		// ft_putendl_fd(buff, 1);
		i = 0;
		while (envlist[i] != NULL)
		{
			/* 우리가 찾는 환경 변수와 일치하다면 buff 에 알맞은 그 값을 넣어 준다. */
			if (ft_strncmp(envlist[i], buff, ft_strlen(buff) + 1) == '=')
			{
				char *temp;
				char *new_trimed;
				ft_strlcpy(g_buf, ft_strchr(envlist[i], '=') + 1, BUFF_MAX);
				temp = ft_strchr(get_param()->cmd_trimed, ' ');
				ft_putendl_fd(temp, 1);
				new_trimed = ft_strjoin(g_buf, temp);
				free(get_param()->cmd_trimed);
				get_param()->cmd_trimed = new_trimed;
				ft_putendl_fd(new_trimed, 1);
				//
				parsing_redirect(get_param()->cmd_trimed);
				if (get_param()->cmd_splited != NULL)
					free_split(get_param()->cmd_splited);
 				get_param()->cmd_splited = ft_split(g_buf, ' ');
				if (get_param()->cmd_redirect != NULL)
					free_3d_split(get_param()->cmd_redirect);
				if (get_param()->symbol_array != NULL)
					free(get_param()->symbol_array);
				get_param()->cmd_redirect = splited_by_redirect(get_param()->cmd_splited,
											&get_param()->symbol_array);
				//
				check_command(get_param()->cmd_splited[0], (char**)argv, (char **)envp);
				// j = ft_strlen(buff) + 1;
				// while (envlist[i][j] != '\0')
				// {
				// 	ft_putchar_fd(envlist[i][j], 1);
				// 	j++;
				// }
				break ;
			}
			i++;
		}
		ft_memset(g_buf, 0, BUFF_MAX);
		// ft_putchar_fd('\n', 1);
	}
	return (0);
}