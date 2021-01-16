#include "minishell.h"

void onoff_flag_bq(int *flag_bq)
{
	if (*flag_bq == 0)
		*flag_bq = 1; /* 큰 따옴표 flag on : 큰 따옴표 안에 있음 */
	else
		*flag_bq = 0; /* 큰 따옴표 flag off : 큰 따옴표 밖에 있음 */
}

void back_slash(char *buff, char *line, t_var *v)
{
	if (v->flag_bq == 0)
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
		onoff_flag_bq(&v->flag_bq);
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