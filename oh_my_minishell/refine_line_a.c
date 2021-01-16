#include "minishell.h"

static void init_value(char *buff, t_var *v)
{
	init_array(buff);
	v->flag_bq = 0;
	v->i = 0;
	v->k = 0;
	v->l = 0; /* ; 로 문자열이 나뉠 때 */
}

int small_quote(char *buff, char *line, t_var *v)
{
	(v->i)++;
	/* 작은 따옴표에 있는 것들 모두 받았습니다 */
	while (line[v->i] != '\'' && line[v->i] != '\0')
	{
		buff[v->k] = line[v->i];
		(v->k)++;
		(v->i)++;
	}
	/* 작은 따옴표가 없을 때 */
	if (line[v->i] == '\0')
	{
		ft_putendl_fd("작은 따옴표 닫아주세요", 2);
		g_status = 1 * 256;
		return (1);
	}
	return (0);
}

char *refine_line(char *line)
{
	char buff[BUFF_MAX];
	t_var v;
	char **envlist;

	if (!line)
		return (NULL);
	envlist = get_param()->envp;
	init_value(buff, &v);
	while (line[v.i] != '\0')
	{
		if (line[v.i] == '\'' && v.flag_bq == 0)
		{
			if (small_quote(buff, line, &v) == 1)
				return (NULL);
		}
		else // 스페이스 같은 경우는 나중에 else의 else에서 그냥 받아들이는 형태로 하면 될 듯
		{
			if (refining_factory(buff, line, &v, envlist) == 1)
				return (NULL);
		}
		(v.i)++;
	}
	return (ft_strdup(buff));
}
