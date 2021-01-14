#include "minishell.h"

char *ft_strsemi(char **str_pointer, int *array, int i)
{
	int size;
	char *ret;
	int temp;

	ret = *str_pointer;
	if (**str_pointer == '\0')
		return (NULL);
	if (array[i] == 0 && **str_pointer != '\0')
	{
		size = ft_strlen(*str_pointer);
		*str_pointer += size;
		return (ret);
	}
	else
	{
		if (i == 0)
		{
			(*str_pointer)[array[i]] = 0;
			(*str_pointer) += (array[i] + 1);
			return (ret);
		}
		else
		{
			temp = array[i] - array[i -1] - 1;
			(*str_pointer)[temp] = 0;
			(*str_pointer) += (temp + 1);
			return (ret);
		}
	}
}
//  echo 222;