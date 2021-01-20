#include "minishell.h"

void back_slash(char *buff, char *line, t_var *v)
{
	/* 큰 따옴표 바깥에 있으면 무시 백슬래쉬를 무시하고 그 뒤에 문자를 넣는다 */
	if (v->flag_bq == 0)
		(v->i)++;
	else if (v->flag_bq == 1 && line[(v->i) + 1] == '"')
		(v->i)++;
	buff[v->k] = line[v->i];
	(v->k)++;
}

int is_redirect(char *buff, char *line, t_var *v)
{
	/* 아예 line을 NUL까지 밀어버리자 */
	if (line[v->i] == '>' && v->flag_bq == 0)
	{
		while (line[v->i] != '\0')
			(v->i)++;
		(v->i)--;
		return (1);
	}
	else if (line[v->i] == '<' && v->flag_bq == 0)
	{
		while (line[v->i] != '\0')
			(v->i)++;
		(v->i)--;
		return (1);
	}
	return (0);
}

int refining_factory(char *buff, char *line, t_var *v, char **envlist)
{
	if (line[v->i] == '"')
		change_flag(&v->flag_bq);
	else if (line[v->i] == '$')
	{
		if (convert_env(buff, line, v, envlist) == 1)
			return(1);
	}
	else if (line[v->i] == '\\')
		back_slash(buff, line, v);
	else
	{
		if (is_redirect(buff, line, v) == 1)
			return (0);
		buff[v->k] = line[v->i];
		(v->k)++;
	}
	return (0);
}