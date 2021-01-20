#include "minishell.h"

/*
** name : init_value
** aim : initialize variables
** @i is for line index
** @k is for buff index(buff is for return string)
** @l is for valid pipe index which is for divide string
*/
static void init_value(char *buff, t_var *v)
{
	init_array(buff);
	v->flag_bq = 0;
	v->i = 0;
	v->k = 0;
	v->l = 0;
}

/*
** name : small_quote
** aim : process string when in small quote
** @while : all charectors regards as literal.
** @if : when small quote is not closed, error returned.
*/
int small_quote(char *buff, char *line, t_var *v)
{
	(v->i)++;
	while (line[v->i] != '\'' && line[v->i] != '\0')
	{
		buff[v->k] = line[v->i];
		(v->k)++;
		(v->i)++;
	}
	if (line[v->i] == '\0')
	{
		ft_putendl_fd("you did not close small quote", 2);
		g_status = 1 * 256;
		return (1);
	}
	return (0);
}

/*
** name : refine_line
** aim : junction for if there's small quote or not
** small quote is go to "small quote"
** without small quote is go to "refining factory"
*/

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
		else
		{
			if (refining_factory(buff, line, &v, envlist) == 1)
				return (NULL);
		}
		(v.i)++;
	}
	return (ft_strdup(buff));
}
