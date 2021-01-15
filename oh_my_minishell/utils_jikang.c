#include "minishell.h"

t_data *get_param()
{
	static t_data param;
	return (&param);
}

int	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f'
			|| c == '\n' || c == '\r');
}

void init_array(char *buff)
{
	int n;

	n = 0;
	while (n < BUFF_MAX)
	{
		buff[n++] = 0;
	}
}

void init_array_int(int *buff)
{
	int n;

	n = 0;
	while (n < BUFF_MAX)
	{
		buff[n++] = 0;
	}
}

void change_flag(int *flag)
{
	if (*flag == 0)
		*flag = 1;
	else if (*flag == 1)
		*flag = 0;
}

void check_semicolon(char *str)
{
	int flag_bq = 0; // 큰 따옴표
	int flag_sq = 0; // 작은 따옴표
	int flag_backslash = 0;
	int i = 0;
	int j = 0;

	init_array_int(get_param()->semi_arr);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			change_flag(&flag_sq);
		else if (str[i] == '"')
			change_flag(&flag_bq);
		else if (str[i] == ';')
		{
			if (i >= 1 && str[i - 1] == '\\')
			{
				i++;
				continue ;
			}
			/* 큰 따옴표, 작은따옴표 안에 없을 때만 */
			if (flag_bq == 0 && flag_sq == 0)
			{
				get_param()->semi_arr[j] = i;
				j++;
			}
		}
		i++;
	}
}