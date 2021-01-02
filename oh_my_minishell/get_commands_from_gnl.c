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


void get_commands_from_gnl(t_list **cmd, char *line, t_setting *setting)
{
	char *substr;
	t_list *new;

	while (TRUE)
	{
		substr = ft_strsep(&line, ";");
		if (substr == NULL)
			break ;
		if (ft_strlen(substr) == 0)
			continue ;
		new = ft_lstnew(substr);
		new->split_by_pipes = ft_split(substr, '|');
		// print_split(new->split); // 이중포인터인 split에 무엇이 담겼나 확인하는 디버깅
		ft_lstadd_back(cmd, new);
	}
}