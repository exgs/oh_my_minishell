#include "minishell.h"

static int	is_same_file(char *path1, char *path2)
{
	struct stat	file1;
	struct stat	file2;

	if (stat(path1, &file1) == -1 || stat(path2, &file2) == -1)
		return (0);
	if (file1.st_dev != file2.st_dev || file1.st_ino != file2.st_ino ||
		file1.st_mode != file2.st_mode || file1.st_mode != file2.st_mode ||
		file1.st_nlink != file2.st_nlink || file1.st_uid != file2.st_uid ||
		file1.st_gid != file2.st_gid || file1.st_rdev != file2.st_rdev ||
		file1.st_size != file2.st_size ||
		file1.st_blksize != file2.st_blksize ||
		file1.st_blocks != file2.st_blocks ||
		file1.st_atime != file2.st_atime ||
		file1.st_mtime != file2.st_mtime || file1.st_ctime != file2.st_ctime)
		return (0);
	return (1);
}

static char			*get_path(char *cmd, char *argv[], char *envp[])
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

// 빌트인에 있으면 함수포인터를 리턴함
static t_builtin	is_builtin(char command[])
{
	if (command == NULL)
		return NULL;
	/* 만약 quotes 있으면 띄어쓰기전까지 읽어서 */
	if (ft_strncmp(string_tolower(command), "echo", 5) == '\0')
		return (execute_echo);
	else if (ft_strncmp(string_tolower(command), "cd", 3) == '\0')
		return (execute_cd);
	else if (ft_strncmp(string_tolower(command), "pwd", 4) == '\0')
		return (execute_pwd);
	else if (ft_strncmp(string_tolower(command), "export", 7) == '\0')
		return (execute_export);
	else if (ft_strncmp(string_tolower(command), "unset", 6) == '\0')
		return (execute_unset);
	else if (ft_strncmp(string_tolower(command), "env", 4) == '\0')
		return (execute_env);
	else if (ft_strncmp(string_tolower(command), "exit", 5) == '\0')
		return (execute_exit);
	else if (ft_strncmp(string_tolower(command), "$", 1) == 0)
		return (execute_dqmark);
	return (NULL);
}

static void	ft_execve(const char *path, char *const argv[], char *const envp[])
{
	pid_t		pid;
	struct stat	buf;

	if (-1 == (pid = fork()))
		return ;
	if (pid == 0)
	{
		if (stat(path, &buf) == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": ",2);
			ft_putendl_fd(strerror(errno), 2);
			exit(127);
		}
		if ((buf.st_mode & S_IFMT) == S_IFDIR)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": ",2);
			ft_putendl_fd(strerror(EISDIR), 2);	// is a directory 만 따로 예외처리
			exit(126);
		}
		if ((execve(path, argv, envp)) == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": ",2);
			ft_putendl_fd(strerror(errno), 2);
			exit(126);
		}
	}
	else
		waitpid(pid, &g_status, 0);
}

void		check_command(char *cmd, char *argv[], char *envp[])
{
	t_builtin	f;
	char		*path;
	char		*slash;
	int			i;

	if (cmd == NULL)
		return ;
	if ((f = is_builtin(cmd)))
		f(cmd, argv, envp);
	else
	{
		if (!(path = get_path(cmd, argv, envp)))
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": command not found", 2);
			g_status = 127 * 256;
			return ;
		}
//		printf("path : %s\n", path);
		if (is_same_file(path, "/usr/bin/env"))
			execute_env(path, argv, envp); // env 뒤에 출력하는거 한번봐야함
		else
			ft_execve(path, argv, envp); // env 뒤에 출력하는거 한번봐야함
		free(path);
	}
}