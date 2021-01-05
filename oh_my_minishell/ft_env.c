#include "minishell.h"

//		export 에서 value를 할당하지 않은 변수들은 출력하지 않음
//		출력되는 순서는 어떤 규칙인지 아직 발견하지 못함
int		ft_env(const char *path, char *const argv[], char *const envp[])
{
	int	i;
	
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