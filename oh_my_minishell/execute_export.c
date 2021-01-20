#include "minishell.h"

static int	is_valid(char str[])
{
	int		i;
	int		end;
	char	*eq;

	if (ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	if ((eq = ft_strchr(str, '=')))
		end = eq - str;
	else
		end = ft_strlen(str);
	i = 0;
	while (i < end)
	{
		if (!ft_isalnum(str[i]) && !(str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	print_envp(char **envp) // DQ붙여서 해야함
{
	char	**tmp;
	char	*eq;
	int		i;

	tmp = vector_dup(envp);
	vector_sort(tmp);
	i = 0;
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], "_=", 2) == '\0')
		{
			i++;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		if ((eq = ft_strchr(tmp[i], '=')))
		{
			write(1, tmp[i], eq - tmp[i] + 1);
			ft_putchar_fd('"', 1);
			write(1, eq + 1, ft_strlen(eq) - 1);
			ft_putchar_fd('"', 1);
		}
		else
			write(1, tmp[i], ft_strlen(tmp[i]));
		write(1, "\n", 1);
		i++;
	}
	vector_clear(tmp);
}


//argv 있으면
	//찾아보고 있으면 값 바꾸기
	//찾아보고 없으면 뒤에 추가
//argv 없으면
	//출력

static void	change_value(char **envp, char argv[])
{
//	printf("-------------------------------\n");
//	printf("envp : %s\n", *envp);
//	printf("argv : %s\n", argv);

	if (ft_strncmp(*envp, argv, ft_strlen(argv) + 1) == '=')
		return ;

	free(*envp);
	*envp = ft_strdup(argv); // 누수주의


}

// a
// a=4
// aa=4

// "a" "a=c" "a" "a=d"
static int	is_exist(char *envp[], char argv[])
{
	int		i;
	int		envp_len;
	int		argv_len;
	int		ret;

	argv_len = ft_strchr(argv, '=') - argv;
	if (argv_len < 0)
		argv_len = ft_strlen(argv);
	i = 0;
	while (envp[i])
	{
		envp_len = ft_strchr(envp[i], '=') - envp[i];
		if (envp_len < 0)
			envp_len = ft_strlen(envp[i]);
		ret = ft_strncmp(envp[i], argv, argv_len + 1);
//		printf("envp : %s\nargv : %s\ndiff : %d\n\n", envp[i], argv, ret);
		if ((argv_len == envp_len) && (ret == '=' || ret == -'=' || ret == '\0'))
			return (i);
		i++;
	}
	return (0);
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

int			execute_export(const char *path, char *const argv[], char *const envp[])
{
	int		i;
	int		j;

	argv++;
	change_split((char **)argv);
	if (vector_size((char **)argv))
	{
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
			if ((j = is_exist((char **)envp, argv[i])))
				change_value((char **)&envp[j], argv[i]);
			else
				vector_push_back((char ***)&envp, argv[i]);
			i++;
		}
	}
	else
		print_envp((char **)envp);
	get_param()->envp = (char **)envp;
	if (g_status != 256)
		g_status = 0;
	return (0);
	(void)path;
}