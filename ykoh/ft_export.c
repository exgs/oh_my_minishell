#include "minishell.h"

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
		ft_putstr_fd("declare -x ", 1);
		if ((eq = ft_strchr(tmp[i], '=')))
		{
			write(1, tmp[i], eq - tmp[i] + 1);
			ft_putchar_fd('"', 1);
			write(1, eq + 1, ft_strlen(eq));
			ft_putchar_fd('"', 1);
		}
		else
			write(1, tmp[i], eq - tmp[i]);
		write(1, "\n", 1);
		i++;
	}
	vector_clear(tmp);
}

/*
static int	is_exist(char *envp[], char argv[])
{
	char	*eq;
	int		ret;
	int		i;

	i = 0;
	while (envp[i])
	{
		if ((eq = ft_strchr(envp[i], '='))) // eq있으면 eq까지 
			ret = ft_strncmp(envp[i], argv, eq - envp[i] + 1);
		else								// eq 없으면 전체
			ret = ft_strncmp(envp[i], argv, ft_strlen(argv) + 1);
		if (ret == '=' || ret == '\0')
			return (1);
		i++;
	}
	return (0);
}


int			ft_export(const char *path, char *const argv[], char *const envp[])
{
	int		i;

	argv++;	//./a.out	다음 부터 시작하기위해서 넣은거
	if (vector_size((char **)argv))	//	환경변수 추가
	{
		i = 0;
		while (argv[i])
		{
			if (is_exist((char **)envp, argv[i]))
				change_value((char **)envp, argv[i]);
			else
				vector_push_back((char ***)&envp, argv[i]);
			i++;
		}
		ft_env(path, argv, envp);
//		get_param()->envp = vector_dup((char **)envp);
//		vector_clear((char **)envp);
	}
	else	//	그냥출력 sortng export
		ft_export_print((char **)envp);
	return (0);
	(void)path;
}

*/

//argv 있으면 
	//찾아보고 있으면 값 바꾸기
	//찾아보고 없으면 뒤에 추가
//argv 없으면 
	//출력

/*
int			ft_export(const char *path, char *const argv[], char *const envp[])
{
	argv++; // 첫번쨰꺼 pass
	int		i;
	int 	j;
	int		ret;
	char	*eq;
	char	**tmp;
	
	tmp = (char **)envp;

//	vector_sort((char **)argv);
	if (vector_size((char **)argv))
	{

		i = 0;
		while (argv[i])
		{
			j = 0;
			while (envp[j])
			{
				if ((eq = ft_strchr(argv[i], '=')))
				{
					ret = ft_strncmp(envp[j], argv[i], eq - argv[i]); // +1?
//					printf("envp : %s\nargv : %s\ndiff : %d\n\n", envp[j], argv[i], ret);
				}
				else
				{
					if (ft_strchr(envp[j], '='))
						continue ;
					ret = ft_strncmp(envp[j], argv[i], ft_strlen(argv[i])); // +1?
					printf("envp : %s\nargv : %s\ndiff : %d\n\n", envp[j], argv[i], ret);
					
				}
				if (ret == '=' || ret == '\0')
				{
					free(envp[j]);
					tmp = (char **)envp;
					tmp[j] = ft_strdup(argv[i]);
				}
				else
				{
					vector_push_back((char ***)&envp, argv[i]);
					break ;
				}
				j++;
			}
			i++;
		}
	}
	else
		print_envp((char **)envp);
	ft_env(path, argv, envp);
	return (0);
	(void)path;
	(void)envp;
}
*/

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
	char	*eq;
	int		ret;

	i = 0;
	while (envp[i])
	{
		if ((eq = ft_strchr(argv, '=')))
			ret = ft_strncmp(envp[i], argv, eq - argv + 1); // =
		else
			ret = ft_strncmp(envp[i], argv, ft_strlen(argv) + 1); // =
//		printf("envp : %s\nargv : %s\ndiff : %d\n\n", envp[i], argv, ret);
		if (ret == '=' || ret == -'=' || ret == '\0')
			return (i);
		i++;
	}
	return (0);
}

int			ft_export(const char *path, char *const argv[], char *const envp[])
{
	int		i;
	int		j;

	argv++; // 첫번쨰꺼 pass
	if (vector_size((char **)argv))
	{
		i = 0;
		while (argv[i])
		{
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
	return (0);
	(void)path;
}