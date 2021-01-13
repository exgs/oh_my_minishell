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