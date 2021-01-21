/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:00:50 by jikang            #+#    #+#             */
/*   Updated: 2021/01/22 01:21:40 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** https://man7.org/linux/man-pages/man2/getcwd.2.html
** char *getcwd(char *buf, size_t size);
*/

int			execute_pwd(const char *path, char *const argv[],
							char *const envp[])
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, PATH_MAX)))
	{
		ft_putendl_fd(strerror(errno), 2);
		g_status = 1 * 256;
	}
	else
	{
		ft_putendl_fd(pwd, 1);
		g_status = 0;
	}
	free(pwd);
	return (1);
	(void)path;
	(void)argv;
	(void)envp;
}
