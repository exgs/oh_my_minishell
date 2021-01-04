/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:50:39 by ykoh              #+#    #+#             */
/*   Updated: 2020/10/05 23:48:59 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <string.h>

typedef struct	s_data
{
	char		**envp;
	char		**argv;
}				t_data;


t_data		*get_param();

int		ft_env(const char *path, char *const argv[], char *const envp[]);
int		ft_export(const char *path, char *const argv[], char *const envp[]);
int		ft_unset(const char *path, char *const argv[], char *const envp[]);


void	vector_erase(char *arr[], int target);
void	vector_sort(char *arr[]);
int		vector_size(char *arr[]);
char	**vector_dup(char *arr[]);
void	vector_clear(char *arr[]);
void	vector_push_back(char **arr[], char str[]);
//void	vector_push_back(char *arr[], char str[]);
#endif
