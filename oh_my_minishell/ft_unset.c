#include "minishell.h"

int		ft_unset(const char *path, char *const argv[], char *const envp[])
{
	int		i;
	int		j;
	int		ret;
	char	*eq;

	argv++; // ./a.out 다음부터 할라고 넣은거 

	//argv에서 not a valid identifier 검출하는 함수 추가해야함 
	i = 0;
	while (argv[i])
	{
		j = 0;
		while (envp[j])
		{
			ret = ft_strncmp(envp[j], argv[i], ft_strlen(argv[i]) + 1);
			if ((eq = ft_strchr(envp[j], '='))) // 값이 할당되어 있는 것도 unset
			{
				if (ret == '=')
					vector_erase((char **)envp, j);
			} 
			else								// 값이 할당되지 않은 것도 unset 테스트 필요함
			{
				if (ret == '\0')
					vector_erase((char **)envp, j);
			}
			j++;
		}
		i++;
	}
	return (0);
	(void)path;
}
