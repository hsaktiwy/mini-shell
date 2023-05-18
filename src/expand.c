#include "mini_shell.h"

char    *expand(t_env *env, char *line)
{
	int		i;
	int		k;
	char	*arg;

	i = 0;
	arg = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && !iswhitespace(line[i + 1]))
		{
			k = 0;
			while (line[k + i + 1] && !iswhitespace(line[k + i + 1]) && line[k + i + 1] != '$')
				k++;
			arg = expand_env_var(env ,&line[i + 1], arg, k);
			i += k + 1;			
		}
		else if(line[i])
		{
			arg = ft_realloc(arg, ft_strlen(arg) + 2);
			ft_strncat(arg, &line[i], 1);
			i++;
		}
	}
	return (arg);
}

char	*reallocated_str(char *str, char *add)
{
	int		size;
	char	*res;

	size = ft_strlen(add);
	res = ft_realloc(str, ft_strlen(str) + size + 1);
	ft_strncat(res, add, size);
	return (res);
}

char    *expand_input(t_env *env, char *line)
{
	int		i;
	int		k;
	char 	c;
	char	*arg;

	i = 0;
	c = '\0';
	arg = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && !iswhitespace(line[i + 1]) && c == '\0')
		{
			k = 0;
			while (line[k + i + 1] && !iswhitespace(line[k + i + 1]) && line[k + i + 1] != '$')
				k++;
			printf("k size of  = %d _ %s\n", k,&line[i + 1]);
			arg = expand_env_var(env ,&line[i + 1], arg, k);
			i += k + 1;			
		}
		else if ((line[i] == '~' && (iswhitespace(line[i + 1])
			|| line[i + 1] == '\0' || line[i + 1] == '/') && c == '\0'))
		{
			printf ("wait what ?\n");
			if (ft_getenv(env, "HOME"))
				arg = reallocated_str(arg, ft_getenv(env, "HOME"));
			else
			{
				arg = ft_realloc(arg, ft_strlen(arg) + 2);
				ft_strncat(arg, &line[i], 1);
				i++;
			}
			i++;
		}
		else if(line[i])
		{
			if (line[i] == '\'' && c == '\0')
				c = '\'';
			else if (line[i] == '\"' && c == '\0')
				c = '\"';
			else if (line[i] == '\'' && c == '\'')
				c = '\0';
			else if (line[i] == '\"' && c == '\"')
				c = '\0';
			arg = ft_realloc(arg, ft_strlen(arg) + 2);
			ft_strncat(arg, &line[i], 1);
			i++;
		}
		printf("??? = %c _ %s\n", line[i], arg);
	}
	free(line);
	return (arg);
}
// void	func_leak()
// {
// 	system("leaks a.out");
// }

// int main(int i, char **argv, char **env)
// {
// 	char *a;
// 	t_env	*env_l;
// 	atexit(func_leak);

// 	env_l = ft_init_env(env);
// 	a = expand_input(env_l, "ls -la $PATH ~ \"$PATH HAHAHA '\" ");
	
// 	printf("%s\n",a);
// 	ft_free_env(&env_l);
// 	return 0;
// }
