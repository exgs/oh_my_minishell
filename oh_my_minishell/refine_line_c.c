#include "minishell.h"

static int is_env_ch(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

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
			ft_bzero(temp, ft_strlen(temp));
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

void insert_dq_in_str(char *str, t_var *v)
{
	int exit_status;

	exit_status = g_status / 256;
	if (exit_status > 100)
	{
		str[(v->k)++] = exit_status / 100 + 48;
		str[(v->k)++] = (exit_status % 100) / 10 + 48;
		str[(v->k)++] = exit_status % 10 + 48;
	}
	else if (exit_status > 10)
	{
		str[(v->k)++] = exit_status / 10 + 48;
		str[(v->k)++] = exit_status % 10 + 48;
	}
	else
	{
		str[(v->k)++] = exit_status + 48;
	}
}

int convert_env(char *buff, char *line, t_var *v, char **envlist)
{
	int j;
	char temp[BUFF_MAX];

	init_array(temp);
	(v->i)++; // $문자 바로 뒤로 인덱스증가
	if (line[v->i] == '$')
	{
		buff[(v->k)++] = '$';
		buff[(v->k)++] = '$';
		return (0);
	}
	else if (line[v->i] == '?')
	{
		/* 여기서 $? 할 것이 아니라 계산도 해줘야함 */
		insert_dq_in_str(buff, v);
		return (0);
	}
	j = 0;
	while (is_env_ch(line[v->i]))
	{
		temp[j] = line[v->i];
		(v->i)++;
		j++;
	}
	(v->i)--; /* is_env_ch 에서 밀려난 환경변수 띄어쓰기 해준다. */
	// ft_putendl_fd(temp, 1);
	/* 이제 temp에 환경 변수와 비교할 문자열이 들어감. */
	/* 환경변수 리스트 돌려서 똑같은 거 찾은 다음 바꿔치기 해줘야함. */
	if (replace_env(temp, envlist) == 1)
	{
		ft_putendl_fd("환경변수 에러", 2);
		g_status = 1 * 256;
		return (1);
	}
	/* 이제 temp에 바뀐 변수 받아왔으니 buff 에 넣어주자 */
	take_buff(buff, temp, &v->k);
	return (0);
}
