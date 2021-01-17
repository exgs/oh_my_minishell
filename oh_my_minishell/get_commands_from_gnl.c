#include "minishell.h"

void	del(void *content)
{
	free(content);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		k = 0;
		while (haystack[i + k] == needle[k] && haystack[i + k])
		{
			if (needle[k + 1] == 0)
				return ((char *)&haystack[i]);
			++k;
		}
		++i;
	}
	return (0);
}

char		*ft_strsep(char **command, const char *delim)
{
	char	*init_str;
	char	*command_index;

	command_index = NULL;
	if (*command == NULL)
		return (NULL);
	if ((*command)[0] == '\0')
		return (NULL);
	init_str = *command;
	command_index = ft_strstr(*command, delim);
	while (delim && *delim && command_index && *command_index)
	{
		*command_index = '\0';
		++command_index;
		++delim;
	}
	*command = command_index;
	return (init_str);
}

int check_firstquotes(char **splited, char *buff, t_var *v)
{
	if (splited[v->i][v->l] == '\'')
	{
		(v->l)++;
		while (splited[v->i][v->l] != '\0')
		{
			if (splited[v->i][v->l] == '\'' && (v->l)++)
				break ;
			buff[(v->k)++] = splited[v->i][v->l];
			(v->l)++;
		}
	}
	else if (splited[v->i][v->l] == '"')
	{
		(v->l)++;
		while (splited[v->i][v->l] != '\0')
		{
			if (splited[v->i][v->l] == '"' && (v->l)++)
				break ;
			buff[(v->k)++] = splited[v->i][v->l];
			(v->l)++;
		}
	}
	else
		return (1);
	return (0);
}

void unseal_firstquotes(char **splited)
{
	t_var v;
	char buff[BUFF_MAX];

	v.i = 0;
	while (splited[v.i] != NULL)
	{
		v.l = 0;	v.k = 0;	init_array(buff);
		/* 맨 처음 앞에 빈 공간 skip */;
		while (ft_is_whitespace(splited[v.i][v.l]))
			(v.l)++;
		if (check_firstquotes(splited, buff, &v) == 1)
		{
			(v.i)++;
			continue ;
		}
		while (splited[v.i][v.l] != '\0')
		{
			buff[(v.k)++] = splited[v.i][v.l];
			(v.l)++;
		}
		free(splited[v.i]);
		splited[v.i] = ft_strdup(buff);
		(v.i)++;
	}
}

char **split_str_by_pipe(char *str, int *buff, t_var *v)
{
	char **new;
	int pipe_num;
	int m, n;	m = 0;	n = 0;

	pipe_num = v->k;
	new = (char **)malloc(sizeof(char *) * (pipe_num + 2));
	if (pipe_num == 0)
	{
		new[0] = ft_strdup(str);
		new[1] = NULL;
		return (new);
	}
	/* buff 에서 인덱스를 받아와서 거기 까지만 해준다 */
	while (m <= pipe_num)
	{
		if (m == 0)
		{
			new[m] = ft_strdup_by_index(str, 0, buff[m] - 1);
		}
		else
		{
			/* 문자열 복붙해주지만, 인덱스를 받아 시작과 끝을 복붙해주는 */
			if (buff[m] == 0)
				buff[m] = ft_strlen(str) + 1;
			new[m] = ft_strdup_by_index(str, buff[m - 1] + 1, buff[m] - 1);
		}
		m++;
	}
	new[m] = NULL;
	return (new);
}

char **split_pipe(char *substr)
{
	t_var v;
	v.flag_bq = 0;
	v.flag_sq = 0;
	int flag_pipe = 0; // 중복되는 파이프 피하기 위해서
	char **str_arr;
	int buff[BUFF_MAX];
	init_array_int(buff);
	v.i = 0; v.l = 0; v.k = 0;
	while (substr[v.i] != '\0')
	{
		if (substr[v.i] == '|')
		{
			/* 따옴표 안에 없는 파이프의 위치값을 buff 에 저장 */
			if (v.flag_bq == 0 && v.flag_sq == 0 && flag_pipe == 0)
			{
				buff[(v.k)++] = v.i;
				flag_pipe = 1;
			}
		}
		else
		{
			if (substr[v.i] == '"')
				change_flag(&v.flag_bq);
			else if (substr[v.i] == '\'')
				change_flag(&v.flag_sq);
			flag_pipe = 0;
		}
		(v.i)++;
	}
	/* 이제 buff 에 담긴 파이프에 따라서 str_arr에 잘라서 넣어주자 */
	str_arr = split_str_by_pipe(substr, buff, &v);
	return (str_arr);
}

void get_commands_from_gnl(t_list **cmd, char *line)
{
	char *substr;
	t_list *new;

	/* 이 함수로 유효한 세미콜론을 확인시켜준다. */
	check_semicolon(line);
	int j;	j = 0;
	int i = 0;
	while (TRUE)
	{
		substr = ft_strsemi(&line, get_param()->semi_arr, i);
		if (substr == NULL)
			break ;
		if (ft_strlen(substr) == 0)
			continue ;
		new = ft_lstnew(substr);
		// new->split_by_pipes = ft_split(substr, '|');
		new->split_by_pipes = split_pipe(substr);
		/* 여기서 new->split_by_pipes 가 따옴표로 시작하면 한꺼풀 걷어주자 */
		unseal_firstquotes(new->split_by_pipes);
		print_split(new->split_by_pipes);
		ft_lstadd_back(cmd, new);
		i++;
	}
}

// echo 111; echo 222; echo 333
