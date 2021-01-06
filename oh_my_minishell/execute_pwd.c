/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:00:50 by jikang            #+#    #+#             */
/*   Updated: 2021/01/06 20:12:55 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** https://man7.org/linux/man-pages/man2/getcwd.2.html
** char *getcwd(char *buf, size_t size);
** getcwd 는 buf 가 NULL 이면, 동적할당을 해준다. 그래서 free 필요.
*/

void execute_pwd(void)
{
	char *pwd;

	if (!(pwd = getcwd(NULL, PATH_MAX)))
		ft_putendl_fd(strerror(errno), 2);
	else
		ft_putendl_fd(pwd, 1);
	free(pwd);
}