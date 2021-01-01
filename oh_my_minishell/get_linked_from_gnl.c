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


void print_cmd_list(t_list *cmd)
{
	int i;
	int lst_length;

	i = 0;
	lst_length = ft_lstsize(cmd);
	while (i < lst_length)
	{
		printf("%d번 째 cmd: %s i_cmd : %d\n", i, cmd->content, cmd->i_cmd);
		cmd = cmd->next;
		i++;
	}
}


void input_raw_cmd(t_list **cmd, char *line)
{
	char *substr;
	t_list *add;

	while (TRUE)
	{
		substr = ft_strsep(&line, " ");
		if (substr == NULL)
			break ;
		if (ft_strlen(substr) == 0)
			continue ;
		add = ft_lstnew(substr);
		add->i_cmd = which_command(add);
		ft_lstadd_back(cmd, add);
	}
}