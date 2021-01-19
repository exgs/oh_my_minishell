#include "minishell.h"

static char *get_path(char *envp[], char str[])
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str) + 1) == '=')
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

static void	change_dir(const char *path, char *envp[])
{
	char	*argv[3];
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX + 1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_status = 1 * 256;
		return ;
	}
	argv[0] = "export";
	argv[2] = NULL;
	argv[1] = ft_strjoin("OLDPWD=", pwd);
	execute_export(argv[0], argv, get_param()->envp);
	free(argv[1]);
	getcwd(pwd, PATH_MAX + 1);
	argv[1] = ft_strjoin("PWD=", pwd);
	execute_export(argv[0], argv, get_param()->envp);
	free(argv[1]);
	g_status = 0;
}

static int	msg_notset(char str[])
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": not set", 2);
	g_status = 1 * 256;
	return (-1);
}

static void change_split(char **argv)
{
	int		i;
	char	*tmp;

	i = 0;
	while (argv[i])
	{
		if ((tmp = refine_line(argv[i])))
		{
			free(argv[i]);
			argv[i] = tmp;
		}
		i++;
	}
}

int			execute_cd(const char *path, char *const argv[], char *const envp[])
{
	char	*tmp;

	tmp = 0;
	change_split((char **)argv + 1);
	path = argv[1];
	if ((argv[1] && ft_strncmp(argv[1], "~", 2) == '\0') ||
		(argv[1] && ft_strncmp(argv[1], "~", 2) == '/'))
	{
		path = ft_strjoin(get_path((char **)envp, "HOME"), argv[1] + 1);
		change_dir(path, (char **)envp);
		free((char *)path);
		return (0);
	}
	else if (!argv[1] || (argv[1] && ft_strncmp(argv[1], "--", 3) == 0))
		tmp = "HOME";
	else if ((argv[1] && ft_strncmp(argv[1], "~-", 3) == 0) ||
			(argv[1] && ft_strncmp(argv[1], "-", 2) == 0))
		tmp = "OLDPWD";
	else if (argv[1] && ft_strncmp(argv[1], "~+", 3) == 0)
		tmp = "PWD";
	if (tmp && !(path = get_path((char **)envp, tmp)))
		return (msg_notset(tmp));
	change_dir(path, (char **)envp);
	if (argv[1] && ft_strncmp(argv[1], "-", 2) == 0)
		ft_putendl_fd(get_path((char **)envp, "PWD"), 1);
	return (0);
}
