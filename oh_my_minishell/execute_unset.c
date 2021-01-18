#include "minishell.h"

static int	is_valid(char str[])
{
	while (*str)
	{
		if (!ft_isalnum(*str) && !(*str == '_'))
			return (0);
		str++;
	}
	return (1);
}

char *erase_dollar(char *str)
{
	char *new;

	if (str[0] == '$')
	{
		new = ft_strdup_by_index(str, 1 , ft_strlen(str));
		return (new);
	}
	return (NULL);
}

static void change_split(char **argv)
{
	char *str;
	/* $를 없애는 */
	str = erase_dollar(argv[1]);
	if (str != NULL)
		free_init(&argv[1], str);
}

int		execute_unset(const char *path, char *const argv[], char *const envp[])
{
	int		i;
	int		j;
	int		ret;
	char	*eq;

	print_split((char **)argv);
	change_split((char **)argv);
	argv++;
	i = 0;
	while (argv[i])
	{
		if (!is_valid(argv[i]))
		{
			g_status = 1 * 256;
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(argv[i++], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			continue ;
		}
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
	if (g_status != 256)
		g_status = 0;
	return (0);
	(void)path;
}
