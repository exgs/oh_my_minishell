#include "minishell.h"

// 폴더 목록중에 경로를 만들 수 있으면 경로만들고 아니면 NULL
static char			*get_path(char *arr, char command[])
{
    DIR				*dir_ptr;
    struct dirent	*file;
	char			*ret[3];

	if(!(dir_ptr = opendir(arr)))
		return (NULL);
	while((file = readdir(dir_ptr)))
	{
		if (ft_strncmp(file->d_name, ".", 2) == '\0' ||
			ft_strncmp(file->d_name, "..", 3) == '\0')
			continue ;
		if (ft_strncmp(file->d_name, command, ft_strlen(command) + 1) == '\0')
		{
			ret[0] = ft_strdup(arr);
			ret[1] = ft_strjoin("/", file->d_name);
			ret[2] = ft_strjoin(ret[0], ret[1]);
//			printf(" ret[2] : %s\n", ret[2]);
			free(ret[0]);
			free(ret[1]);
			closedir(dir_ptr);
			return (ret[2]); // close 안된거
		}
	}
	closedir(dir_ptr);
	return (NULL);
}

// 커맨드인지 확인하고 path를 할당해서 리턴함
static char			*is_command(char command[], char *envp[])
{
	char			**arr;
	char			*ret;
	int				i;

	if (command == NULL)
		return (NULL);
	while (*envp && ft_strncmp(*envp, "PATH", 5) != '=')
		envp++;
	if (!ft_strchr(*envp, '='))
		return (NULL);
	arr = ft_split(ft_strchr(*envp, '=') + 1, ':');
	i = 0;
	while (arr[i])
	{
		if ((ret = get_path(arr[i], command)))
			break ;
		i++;
	}
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (ret);
}

// 빌트인에 있으면 함수포인터를 리턴함
static t_builtin	is_builtin(char command[])
{
	if (command == NULL)
		return NULL;
	if (ft_strncmp(string_tolower(command), "echo", 5) == '\0')
		return (execute_echo);
	else if (ft_strncmp(string_tolower(command), "/bin/echo", 10) == '\0')
		return (execute_echo);
	else if (ft_strncmp(string_tolower(command), "cd", 3) == '\0')
		return (execute_cd);
	else if (ft_strncmp(string_tolower(command), "/usr/bin/cd", 15) == '\0')
		return (execute_cd);
	else if (ft_strncmp(string_tolower(command), "pwd", 4) == '\0')
		return (execute_pwd);
	else if (ft_strncmp(string_tolower(command), "/bin/pwd", 15) == '\0')
		return (execute_pwd);
	else if (ft_strncmp(string_tolower(command), "export", 7) == '\0')
		return (execute_export);
	else if (ft_strncmp(string_tolower(command), "unset", 6) == '\0')
		return (execute_unset);
	else if (ft_strncmp(string_tolower(command), "env", 4) == '\0')
		return (execute_env);
	else if (ft_strncmp(string_tolower(command), "/usr/bin/env", 15) == '\0')
		return (execute_env);
	else if (ft_strncmp(string_tolower(command), "exit", 5) == '\0')
		return (execute_exit);
	else if (ft_strncmp(string_tolower(command), "$?", 3) == '\0')
		return (execute_dqmark);
	// else if (ft_strncmp(string_tolower(command), "/", 1) == 0 ||
	// 			ft_strncmp(string_tolower(command), ".", 1) == 0) //<-- 어짜피 NUL 문자인데, 여기서는 딱 문자하나 비교해서 0
	// 	return (execute_is_dir_file);
	return (NULL);
}

// 커맨드가 빌트인인지 아닌지 확인해줌, argv[]는 cmd_splited
void check_command(char *cmd, char *argv[], char *envp[])
{
	t_builtin	f;
	char		*path;
	
	if (cmd == NULL)
		return;
	if (ft_strncmp(string_tolower(cmd), "/", 1) == 0 ||
				ft_strncmp(string_tolower(cmd), ".", 1) == 0) //<-- 어짜피 NUL 문자인데, 여기서는 딱 문자하나 비교해서 0
	{
		execute_is_dir_file(cmd, argv, envp);
		return ;
	}
	if ((f = is_builtin(cmd)))
		f(cmd, argv, envp);
	else
	{
		if ((path = is_command(cmd, envp)))
			is_execve(path, argv, envp);
			// execve(path, argv, envp);
		else
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(cmd, 1);
			ft_putendl_fd(": command not found", 1);
			g_status = 127 * 256;
		}
		free(path);
	}
}