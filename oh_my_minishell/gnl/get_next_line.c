/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:25:54 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 03:48:35 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_read_before(char **remain, char **line)
{
	char *remain_temp;

	if (change_newline_to_zero(*remain) == 1)
	{
		remain_temp = *remain;
		*line = ft_strdup2(*remain);
		*remain = ft_strdup2(ft_strchr2(*remain, 0) + 1);
		free(remain_temp);
		return (1);
	}
	else
		return (0);
}

int	change_newline_to_zero(char *remain)
{
	int i;

	if (remain == NULL)
		return (0);
	i = 0;
	while (remain[i])
	{
		if (remain[i] == '\n')
		{
			remain[i] = '\0';
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_next_line_initial_error(int fd, char **line)
{
	char	buffer[1];

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL || read(fd, buffer, 0) < 0)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	char		buffer[BUFFER_SIZE + 1];
	static char	*remain;
	char		*remain_temp;

	if (get_next_line_initial_error(fd, line) == 0)
		return (-1);
	if (remain != NULL && check_read_before(&remain, line) == 1)
		return (1);
	ft_memset2(buffer, 0, BUFFER_SIZE + 1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		remain_temp = remain;
		remain = ft_strjoin2(remain, buffer);
		free(remain_temp);
		if (check_read_before(&remain, line) == 1)
			return (1);
		ft_memset2(buffer, 0, BUFFER_SIZE + 1);
	}
	*line = ft_strdup2(remain);
	free(remain);
	remain = NULL;
	return (0);
}
