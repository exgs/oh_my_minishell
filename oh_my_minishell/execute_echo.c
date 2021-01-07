#include "minishell.h"

void execute_echo(char *one_cmd_trimed)
{
	int i;
	/* echo <--는 건너띄고 index 5번 부터 검사시작 */
	i = 5;
	/* echo 하고 띄어쓰기는 무시하고 넘어가기(is_whitespace) */
	while (ft_is_whitespace(one_cmd_trimed[i]))
		i++;
	/* 이제 진짜 출력할 문자열 온 거임 "hi hi hi"*/
	while (one_cmd_trimed[i] != '\0')
	{
		/* 작은 따온표를 만나면 다시 작은 따온표를 만날 때 까지 */
		/* 작은 따온표는 강한 문자열의 표시이므로 환경변수나 백슬래쉬로 문자변환 안된다 */
		/* 그래서 우선순위의 최상단에 있기에 독립적인 if 문으로 올렸음 */
		if (one_cmd_trimed[i] == '\'')
		{
			i++;
			if (one_cmd_trimed[i] == '\0')
			{
				ft_putstr_fd("\nerror! : 따온표 에러\n", 1);
				break ;
			}
			while (one_cmd_trimed[i] != '\'' && one_cmd_trimed[i] != '\0')
			{
				ft_putchar_fd(one_cmd_trimed[i], 1);
				i++;
			}
			i++;
		}
		else
		{
			/* 큰 따온표를 만나면 다시 큰 따온표를 만날 때 까지 */
			if (one_cmd_trimed[i] == '"')
			{
				/* 첫 따온표 스킵 */
				i++;
				while (one_cmd_trimed[i] != '"' && one_cmd_trimed[i] != '\0')
				{
					if (one_cmd_trimed[i] == '\\')
					{
						i++;
						if (one_cmd_trimed[i] == '\\')
						{
							ft_putchar_fd('\\', 1);
							i++;
						}
						else if (one_cmd_trimed[i] == '\'')
						{
							ft_putchar_fd('\'', 1);
							i++;
						}
						else if (one_cmd_trimed[i] == '\"')
						{
							ft_putchar_fd('\"', 1);
							i++;
						}
					}
					else
					{
						ft_putchar_fd(one_cmd_trimed[i], 1);
						i++;
					}
				}
				i++;
			}
			else
			{
				if (one_cmd_trimed[i] == '\\')
				{
					i++;
					if (one_cmd_trimed[i] == '\\')
					{
						ft_putchar_fd('\\', 1);
						i++;
					}
					else if (one_cmd_trimed[i] == '\'')
					{
						ft_putchar_fd('\'', 1);
						i++;
					}
					else if (one_cmd_trimed[i] == '\"')
					{
						ft_putchar_fd('\"', 1);
						i++;
					}
				}
				else
				{
					ft_putchar_fd(one_cmd_trimed[i], 1);
					i++;
				}
			}
		}
	}
	/* -n 옵션 들어갈 시 무시 */
	ft_putchar_fd('\n', 1);
	g_status = 0;
}