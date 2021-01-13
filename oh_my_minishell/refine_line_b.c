#include "minishell.h"

void onoff_flag_bq(int *flag_bq)
{
	if (*flag_bq == 0)
		*flag_bq = 1; /* 큰 따옴표 flag on */
	else
		*flag_bq = 0; /* 큰 따옴표 flag off */
}

void back_slash(char *buff, char *line, int *k, int *i)
{
	(*i)++;
	buff[*k] = line[*i];
	(*k)++;
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
		back_slash(buff, line, &v->k, &v->i);
	else
	{
		if (line[v->i] == ';')
			get_param()->semi_arr[(v->l)++] = v->k; // <-- semi-colon 찾고 숫자 대입
		buff[v->k] = line[v->i];
		(v->k)++;
	}
	return (0);
}