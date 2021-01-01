#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

int		ft_strlen2(char *str);
char	*ft_strdup2(char *str);
void	ft_memset2(char *memory, int c, int size);
char	*ft_strchr2(char *str, char c);
char	*ft_strjoin2(char *head, char *tail);
int		check_read_before(char **remain, char **line);
int		change_newline_to_zero(char *remain);
int		get_next_line_initial_error(int fd, char **line);
int		get_next_line(int fd, char **line);

#endif
