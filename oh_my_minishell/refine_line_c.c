#include "minishell.h"

int check_env(char *temp, char **envlist)
{
	int i;
	int j;
	char *var;

	i = 0;
	while (envlist[i] != NULL)
	{
		/* 우리가 찾는 환경 변수와 일치하다면 buff 에 알맞은 그 값을 넣어 준다. */
		if (ft_strncmp(envlist[i], temp, ft_strlen(temp) + 1) == '=')
		{
			var = ft_strchr(envlist[i], '=');
			var++; /* '=' 이후가 진짜이니 +1 해준다. */
			j = 0;
			while (*var != '\0')
			{
				temp[j] = *var;
				var++;	j++;
			}
			return (0); // 0 이 정상적으로 찾음
		}
		i++;
	}
	return (1); // 1이 환경변수 찾지 못함.
}

int replace_env(char *temp, char **envlist)
{
	int i;
	int j;

	if (temp[0] == 0)
	{
		temp[0] = '$';
		return(0);
	}
	if (ft_strncmp("?", temp, ft_strlen(temp) + 1) == 0)
	{
		temp[0] = '$';
		temp[1] = '?';
		return (0);
	}
	if (check_env(temp, envlist) == 0)
		return (0);
	return (1);
}

void take_buff(char *buff, char *temp, int *k)
{
	int j;

	j = 0;
	while (temp[j] != '\0')
	{
		buff[*k] = temp[j];
		(*k)++;
		j++;
	}
}

int convert_env(char *buff, char *line, t_var *v, char **envlist)
{
	int j;
	char temp[BUFF_MAX];

	init_array(temp);
	(v->i)++;
	j = 0;
	while (line[v->i] != ' ' && line[v->i] != '\0' && line[v->i] != '"' && line[v->i] != '\'' && line[v->i] != '$' && line[v->i] != '/' && line[v->i] != '.')
	{
		temp[j] = line[v->i];
		(v->i)++;
		j++;
	}
	if (line[v->i] == '\'' || line[v->i] == '$' || line[v->i] == '/')
		(v->i)--;
	// ft_putendl_fd(temp, 1);
	/* 이제 temp에 환경 변수와 비교할 문자열이 들어감. */
	/* 환경변수 리스트 돌려서 똑같은 거 찾은 다음 바꿔치기 해줘야함. */
	if (replace_env(temp, envlist) == 1)
	{
		ft_putendl_fd("환경변수 에러", 1);
		g_status = 1 * 256;
		return (1);
	}
	/* 이제 temp에 바뀐 변수 받아왔으니 buff 에 넣어주자 */
	take_buff(buff, temp, &v->k);
	return (0);
}
