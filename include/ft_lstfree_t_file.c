
#include "include.h"

void	ft_lstfree_t_file(t_list **node)
{
	t_file	*file;

	if (*node)
	{
		file = (*node)->content;
		free(file->a_file);
		ft_lstfree_node(node);
	}
}
