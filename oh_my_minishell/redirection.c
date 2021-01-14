#include "minishell.h"

typedef struct s_index
{
	int i;
	int j;
	int z;
	int before;
	int cnt;
	int redir_num;
}t_index;

void s_index_bzero(t_index *index)
{
	index->before = 0;
	index->cnt = 0;
	index->i = 0;
	index->j = 0;
	index->redir_num = 0;
	index->z = 0;
}

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

void input_symbol(char **split, char *symbol_array, t_index *index)
{
	if (is_redirect(split[index->i]) == LEFT)
			symbol_array[index->z++] = LEFT;
		else if (is_redirect(split[index->i]) == RIGHT)
			symbol_array[index->z++] = RIGHT;
		else if (is_redirect(split[index->i]) == D_RIGHT)
			symbol_array[index->z++] = D_RIGHT;
		else
			symbol_array[index->z++] = ERROR;
}

void		splited_by_redirect_norm(char ***divid, char **split, char *symbol_array, t_index *index)
{
	char *str;
	int j;
	
	j = 0;
	while (split[index->i])
	{
		str = split[index->i];
		if (is_redirect(split[index->i]) != 0)
		{
			input_symbol(split, symbol_array, index);
			divid[index->cnt] = malloc(sizeof(char *) * (index->i - index->before + 1));
			index->j = 0;
			while (index->before < index->i)
			{	
				divid[index->cnt][index->j] = strdup(split[index->before]);
				index->before++;
				index->j++;
			}
			divid[index->cnt][index->j] = NULL;
			index->before = index->i + 1;
			index->cnt++;
		}
		index->i++;
	}
}

char	***splited_by_redirect(char **one_cmd_splited, char **array)
{
	char ***divid;
	char **split = one_cmd_splited;
	char *symbol_array;
	char *temp;
	int p;
	t_index index;
	
	s_index_bzero(&index);
	index.redir_num = redirect_num(one_cmd_splited);
	divid = malloc(sizeof(char **) * (index.redir_num + 1 + 1));
	symbol_array = malloc(sizeof(char) * (index.redir_num + 1));
	splited_by_redirect_norm(divid, split, symbol_array, &index);
	p= 0;
	divid[index.cnt] = malloc(sizeof(char *) * (index.i - index.before + 1));
	while (index.before < index.i)
	{	
		temp = split[index.before];
		divid[index.cnt][p++] = strdup(split[index.before]);
		index.before++;
	}
	divid[index.cnt][p] = NULL;
	divid[index.redir_num + 1] = NULL;
	symbol_array[index.redir_num] = 0;
	*array = symbol_array;
	return (divid);
}

int parsing_redirect(char *str)
{
	int i;
	int k;
	
	ft_memset(g_buf, 0, 1000);
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		g_buf[k++] = str[i];
		if ((str[i] == '<' || str[i] == '>') && (str[i+1] == '<' || str[i+1] == '>'))
		{
			i++;
			continue;
		}
		else if((str[i] == '<' || str[i] == '>') && (str[i+1] != '>' && str[i+1] != '<'))
		{
			g_buf[k++] = ' ';
		}
		else if((str[i] != '<' && str[i] != '>') && (str[i+1] == '>' || str[i+1] == '<'))
		{
			g_buf[k++] = ' ';
		}
		i++;
	}
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
	check_command(get_param()->cmd_redirect[0][0], get_param()->cmd_redirect[0], get_param()->envp);
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
	check_command(get_param()->cmd_redirect[0][0], get_param()->cmd_redirect[0], get_param()->envp);
	return (1);
}

int execute_nopipe_redirect()
{
	char *symbols = get_param()->symbol_array;
	int i = 0;
	int mkfile = 0;
	while (symbols[i] != 0)
	{
		if (symbols[i] == LEFT)
		{
			if (-1 == redirect_left(i))
				return (-1);
		}
		else if (symbols[i] == RIGHT)
		{
			mkfile++;
			if (-1 == redirect_right(i))
				return (-1);
		}
		else if (symbols[i] == D_RIGHT)
		{
			mkfile++;
			if (-1 == redirect_d_right(i))
				return (-1);
		}
		i++;
	}
	if (mkfile == 0)
		check_command(get_param()->cmd_redirect[0][0], get_param()->cmd_redirect[0], get_param()->envp);
	dup_initalize();
	return (1);
}