#include "minishell.h"

static char *get_path(char *envp[], char str[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str) + 1) == '=')
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

static void	change_dir(char *path, char *envp[])
{
	char	*pwd;
	char	*oldpwd;
	char	*argv[3];
	char	*tmp;

	tmp = ft_strdup(path);
	if (chdir(path) == -1)
		ft_putendl_fd(strerror(errno), 2);
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", get_path(envp, "PWD"));
		argv[0] = "export";
		argv[1] = oldpwd;
		argv[2] = NULL;
		execute_export(argv[0], argv, envp);
		pwd = ft_strjoin("PWD=", tmp);
		argv[1] = pwd;
		execute_export(argv[0], argv, envp);
		free(tmp);
		free(pwd);
		free(oldpwd);
	}
}

int			execute_cd(const char *path, char *const argv[], char *const envp[])
{
	char *path_;

	if ((argv[1] && ft_strncmp(argv[1], "~", 2) == 0) ||
		(argv[1] && ft_strncmp(argv[1], "--", 3) == 0) ||
		!argv[1])
		path_ = get_path((char **)envp, "HOME");
	else if ((argv[1] && ft_strncmp(argv[1], "~-", 3) == 0) ||
			(argv[1] && ft_strncmp(argv[1], "-", 2) == 0))
		path_ = get_path((char **)envp, "OLDPWD");
	else if (argv[1] && ft_strncmp(argv[1], "~+", 3) == 0)
		path_ = get_path((char **)envp, "PWD");
	else
		path_ = argv[1];
	change_dir(path_, (char **)envp);
	if (argv[1] && ft_strncmp(argv[1], "-", 2) == 0)
		ft_putendl_fd(get_path((char **)envp, "PWD"), 1);
	return (0);
	(void)path;
	(void)argv;
	(void)envp;
}