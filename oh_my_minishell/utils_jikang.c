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
