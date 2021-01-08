/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:00:50 by jikang            #+#    #+#             */
/*   Updated: 2021/01/09 03:30:46 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** https://man7.org/linux/man-pages/man2/getcwd.2.html
** char *getcwd(char *buf, size_t size);
** getcwd 는 buf 가 NULL 이면, 동적할당을 해준다. 그래서 free 필요.
*/

int execute_pwd(const char *path, char *const argv[], char *const envp[])
{
	char *pwd;

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
}