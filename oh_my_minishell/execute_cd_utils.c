/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 03:30:14 by yunslee           #+#    #+#             */
/*   Updated: 2021/01/21 03:35:18 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_home_cd(const char *str)
{
	if ((str && ft_strncmp(str, "~", 2) == '\0') ||
		(str && ft_strncmp(str, "~", 2) == '/'))
		return (TRUE);
	else
		return (FALSE);
}
