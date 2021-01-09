#include "minishell.h"

static int		is_redirect(char *str)
{
	if (str[0] == '>' || str[0] == '<')
	{
		if (!ft_strncmp(str, ">>", 3))
			return (D_RIGHT);
		else if (!ft_strncmp(str, ">", 2))
			return (RIGHT);
		else if (!ft_strncmp(str, "<", 2))
			return (LEFT);
		return (ERROR);
	}
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
			else
				symbol_array[z++] = ERROR;
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

int parsing_redirect(char *str)
{
	int i, k;
	k = 0;
	while (k < 1000)
		g_buf[k++] = 0;
	i = 0; k = 0;
	while (str[i] != '\0')
	{
		g_buf[k] = str[i];
		k++;
		if ((str[i] == '<' || str[i] == '>') && (str[i+1] == '<' || str[i+1] == '>'))
		{
			i++;
			continue;
		}
		else if((str[i] == '<' || str[i] == '>') && (str[i+1] != '>' && str[i+1] != '<'))
		{
			g_buf[k] = ' ';
			k++;
		}
		else if((str[i] != '<' && str[i] != '>') && (str[i+1] == '>' || str[i+1] == '<'))
		{
			g_buf[k] = ' ';
			k++;
		}
		i++;
	}
	printf("str  is :%s\n", str);
	printf("buf is :%s\n", g_buf);
	return (1);
}

static int redirect_left(int i)
{
	int fd;
	char *path = get_param()->cmd_redirect[i + 1][0];
	if (get_param()->cmd_redirect[i + 1][1] != NULL)
		return (-1);
	fd = open(path, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

static int redirect_right(int i)
{
	int fd;
	char *path = get_param()->cmd_redirect[i + 1][0];
	if (get_param()->cmd_redirect[i + 1][1] != NULL)
		return (-1);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int redirect_d_right(int i)
{
	int fd;
	char *path = get_param()->cmd_redirect[i + 1][0];
	if (get_param()->cmd_redirect[i + 1][1] != NULL)
		return (-1);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0755);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
	return (1);
}

int execute_nopipe_redirect()
{
	char *symbols = get_param()->symbol_array;
	int i = 0;
	while (symbols[i] != 0)
	{
		if (symbols[i] == LEFT)
		{
			if (-1 == redirect_left(i))
				return (-1);
		}
		else if (symbols[i] == RIGHT)
		{
			if (-1 == redirect_right(i))
				return (-1);
		}
		else if (symbols[i] == D_RIGHT)
		{
			if (-1 == redirect_d_right(i))
				return (-1);
		}
		i++;
	}
	check_command(get_param()->cmd_redirect[0], get_param()->envp);
	dup_initalize();
	return (1);
}