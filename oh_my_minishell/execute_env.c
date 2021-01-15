#include "minishell.h"

//		export 에서 value를 할당하지 않은 변수들은 출력하지 않음
//		출력되는 순서는 어떤 규칙인지 아직 발견하지 못함
int		execute_env(const char *path, char *const argv[], char *const envp[])
{
	int	i;
	
	if (argv[1] != NULL)
	{
		g_status = 256 * 127;
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putendl_fd(": No such file or directory", 1);
		return (-1);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
	(void)path;
	(void)argv;
}