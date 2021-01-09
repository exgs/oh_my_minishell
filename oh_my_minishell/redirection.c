#include "minishell.h"

static int		is_redirect(char *str)
{
	if (!strncmp(str, ">>", 3))
		return (D_RIGHT);
	else if (!strncmp(str, ">", 2))
		return (RIGHT);
	else if (!strncmp(str, "<", 2))
		return (LEFT);
	return (FALSE);
}

static int		redirect_num(char **one_cmd_splited)
{
	int i = 0;
	int cnt = 0;
	while (one_cmd_splited[i])
	{
		if (is_redirect(one_cmd_splited[i]) != 0)
			cnt++;
		i++;
	}
	return (cnt);
}

char	***splited_by_redirect(char **one_cmd_splited, char **array)
{
	int i = 0;
	char ***divid;
	char **split = one_cmd_splited;
	char *symbol_array;
	int redir_num;
	int z = 0;
	
	redir_num = redirect_num(one_cmd_splited);
	divid = malloc(sizeof(char **) * (redir_num + 1 + 1));
	symbol_array = malloc(sizeof(char) * (redir_num + 1));
	int before = 0;
	int cnt = 0;
	char *str;
	while (split[i])
	{
		str = split[i];
		if (is_redirect(split[i]) != 0)
		{
			if (is_redirect(split[i]) == LEFT)
				symbol_array[z++] = LEFT;
			else if (is_redirect(split[i]) == RIGHT)
				symbol_array[z++] = RIGHT;
			else if (is_redirect(split[i]) == D_RIGHT)
				symbol_array[z++] = D_RIGHT;
			divid[cnt] = malloc(sizeof(char *) * (i - before + 1));
			int j = 0;
			while (before < i)
			{	
				// printf("%s\n", split[before]);
				divid[cnt][j] = strdup(split[before]);
				before++;
				j++;
			}
			divid[cnt][j] = NULL;
			before = i + 1;
			cnt++;
		}
		i++;
	}
	char *temp;
	int p = 0;
	divid[cnt] = malloc(sizeof(char *) * (i - before + 1));
	while (before < i)
	{	
		temp = split[before];
		// printf("%s\n", temp);
		divid[cnt][p] = strdup(split[before]);
		before++;
		p++;
	}
	divid[cnt][p] = NULL;
	divid[redir_num + 1] = NULL;
	symbol_array[redir_num] = 0;
	*array = symbol_array;
	return (divid);
}
