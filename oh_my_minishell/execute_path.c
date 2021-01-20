#include "minishell.h"

static	int execute_path_norm(const char *path, char *const argv[], char *const envp[])
{
	
}

static	int command_not_found_g_status(char *str)
{
	ft_putendl_fd(str, 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putnbr_fd(g_status / 256, 2);
	ft_putendl_fd(": command not found", 2);
	g_status = 127 * 256;
	return (0);
}

static void copy_pathname(char *str, char *buff)
{
	int i;

	init_array(buff);
	i = 1;
	while (str[i] != '\0' && str[i] != ' ')
	{
		buff[i - 1] = str[i];
		i++;
	}
}

int		execute_path(const char *path, char *const argv[], char *const envp[])
{
	char buff[BUFF_MAX];
	char *str;
	int i = 0;
	char **envlist;
	
	str = get_param()->cmd_trimed;
	envlist = get_param()->envp;
	if (path[1] == '?')
		return (command_not_found_g_status(str));
	else
	{
		copy_pathname(str, buff);
		while (envlist[i] != NULL)
		{
			if (ft_strncmp(envlist[i], buff, ft_strlen(buff) + 1) == '=')
			{
				char *temp;
				char *new_trimed;
				ft_strlcpy(g_buf, ft_strchr(envlist[i], '=') + 1, BUFF_MAX); 
				temp = ft_strchr(get_param()->cmd_trimed, ' ');
				ft_putendl_fd(temp, 1);
				new_trimed = ft_strjoin(g_buf, temp);
				free(get_param()->cmd_trimed);
				get_param()->cmd_trimed = new_trimed;
				ft_putendl_fd(new_trimed, 1);
				//
				parsing_redirect(get_param()->cmd_trimed);
				if (get_param()->cmd_splited != NULL)
					free_split(get_param()->cmd_splited);
 				get_param()->cmd_splited = ft_split(g_buf, ' ');
				if (get_param()->cmd_redirect != NULL)
					free_3d_split(get_param()->cmd_redirect);
				if (get_param()->symbol_array != NULL)
					free(get_param()->symbol_array);
				get_param()->cmd_redirect = splited_by_redirect(get_param()->cmd_splited,
											&get_param()->symbol_array);
				//
				check_command(get_param()->cmd_splited[0], (char**)argv, (char **)envp);
				break ;
			}
			i++;
		}
		ft_memset(g_buf, 0, BUFF_MAX);
	}
	return (0);
}
