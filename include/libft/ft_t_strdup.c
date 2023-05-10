#include "libft.h"

int		ft_t_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_t_strdup(char **str)
{
	int		size;
	char	**res;
	int		i;

	if (!str)
		return (NULL);
	size = ft_t_strlen(str);
	res = (char **)malloc(sizeof(char *) * size + 1);
	if (!res)
		return (NULL);
	res[size] = NULL;
	i = -1;
	while (str[++i])
		res[i] = ft_strdup(str[i]);
	return (res);
}
