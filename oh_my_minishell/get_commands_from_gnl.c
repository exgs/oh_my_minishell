#include "minishell.h"

void	del(void *content)
{
	free(content);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		k = 0;
		while (haystack[i + k] == needle[k] && haystack[i + k])
		{
			if (needle[k + 1] == 0)
				return ((char *)&haystack[i]);
			++k;
		}
		++i;
	}
	return (0);
}

char		*ft_strsep(char **command, const char *delim)
{
	char	*init_str;
	char	*command_index;

	command_index = NULL;
	if (*command == NULL)
		return (NULL);
	if ((*command)[0] == '\0')
		return (NULL);
	init_str = *command;
	command_index = ft_strstr(*command, delim);
	while (delim && *delim && command_index && *command_index)
	{
		*command_index = '\0';
		++command_index;
		++delim;
	}
	*command = command_index;
	return (init_str);
}


void get_commands_from_gnl(t_list **cmd, char *line)
{
	char *substr;
	char *refined_line;
	char *temp;
	t_list *new;
	int j;
	refined_line = refine_line(line);
	temp = refined_line;
	// j = 0;
	// while (j < BUFF_MAX)
	// {
	// 	if (get_param()->semi_arr[j] == 0)
	// 	{
	// 		printf("이제 없음\n");
	// 		break ;
	// 	}
	// 	printf("semi_arr[%d] : %d\n", j, get_param()->semi_arr[j]);
	// 	j++;
	// }
	int i = 0;
	while (TRUE)
	{
		substr = ft_strsemi(&refined_line, get_param()->semi_arr, i);
		ft_putendl_fd(substr, 1);
		if (substr == NULL)
			break ;
		if (ft_strlen(substr) == 0)
			continue ;
		new = ft_lstnew(substr);
		new->split_by_pipes = ft_split(substr, '|');
		ft_lstadd_back(cmd, new);
		i++;
	}
	free(temp);
}

// echo 111; echo 222; echo 333