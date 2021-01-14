#include "minishell.h"

char		*find_process_name(char *path)
{
	char *file_name;
	int i;
	int j;

	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '/')
			j = i;
		i++;
	}
	file_name = path + j + 1;
	return (file_name);
}

int		execute_process(char *path)
{
	char **new_path;
	pid_t pid;

	/* 마지막 /를 찾고 그 뒤를 파일 이름으로 판단 */
	new_path = malloc(sizeof(char *) * 2);
	new_path[0] = ft_strdup(find_process_name((char *)path));
	new_path[1] = NULL;

	if (-1 == (pid = fork()))
		return (-1);
	if (pid == 0)
	{
		execve(path, new_path, get_param()->envp);
	}
	else
	{
		waitpid(pid, &g_status, 0);
	}
	free_split(new_path);
	return (-1);
}


/* */
int			execute_is_dir_file(const char *path, char *const argv[], char *const envp[])
{
	struct stat sb;
	char *cmd;
	/* /user/bin/env 하면 환경변수 리스트 출력된다. */
	if (ft_strncmp(path, "/usr/bin/env", 13) == '\0')
	{
		return(execute_env(path, argv, envp));
	}
	else if (-1 == stat(path, &sb))
	{
		/* 여기들어오는 게 비정상상태(잘못된 경로)*/
		ft_putstr_fd("minishell: ", 1);
		ft_putendl_fd("no such file or directory :", 1);
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
		// ft_putnbr_fd(!stat(path, &sb), 1);
		g_status = 127 * 256;
		return (0);
	}
	else
	{
		/* 여기들어오는 게 정상상태(올바른 경로)*/
		// if (execute_process((char *)path) == -1)
		if (S_ISDIR(sb.st_mode) == 0 && (sb.st_mode & S_IXUSR))
		{
			pid_t pid;
			pid = fork();
			if (pid == 0) 
			{
				execve(path, argv, envp);
			}
			else
			{
				waitpid(pid, NULL, 0);
			}
			// cmd = find_process_name((char *)path);
			// check_command(cmd, (char **)argv, (char **)envp);
			
			g_status = 1 * 256;
			return (1);
		}
		else
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(path, 1);
			if (S_ISDIR(sb.st_mode))
			{
				ft_putendl_fd(": is a directory", 1);
				g_status = 126 * 256;
			}
			else if (!(sb.st_mode & S_IXUSR)) /* user가 실행권한이 없으면 */
			{
				ft_putendl_fd(": Permission denied", 1);
				g_status = 126 * 256;
			}
		}
		return (0);
	}
}
