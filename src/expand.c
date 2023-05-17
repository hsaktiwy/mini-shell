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

// int main(int i, char **argv, char **env)
// {
// 	char *a;
// 	t_env	*env_l;

// 	env_l = ft_init_env(env);
// 	a = expand(env_l, "ls -la '$PATH' \"$PATH\" ");
// 	printf("%s\n",a);
// 	return 0;
// }
