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
		new->split_by_pipes = ft_split(substr, '|');
		/* 여기서 new->split_by_pipes 가 따옴표로 시작하면 한꺼풀 걷어주자 */
		unseal_firstquotes(new->split_by_pipes);
		print_split(new->split_by_pipes);
		ft_lstadd_back(cmd, new);
		i++;
	}
}

// echo 111; echo 222; echo 333
