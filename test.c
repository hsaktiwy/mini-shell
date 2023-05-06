#include <sys/stat.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "src/mini_shell.h"

// void	ft_lstadd_in_index(t_list **list, t_list *new, int index)
// {
// 	t_list	*previous;
// 	t_list	*next_n;

// 	next_n = *list;
// 	previous = next_n;
// 	if (index == 0 || !(*list))
// 	{
// 		new->next = next_n;
// 		*list = new;
// 		return ;
// 	}
// 	while (next_n->next && index--)
// 	{
// 		previous = next_n;
// 		next_n = next_n->next;
// 	}

// 	previous->next = new;
// 	if (previous != new)
// 		new->next = next_n;
// }

void	ft_lstfree_node(t_list **node)
{
	if (*node)
	{
		free((*node)->content);
		free((*node));
		*node = NULL;
	}
}
void	ft_lstdelete_index(t_list **list, int index)
{
	t_list	*previous;
	t_list	*node;

	if (!(*list))
		return ;
	if (index == 0)
	{
		node = *list;
		*list = (*list)->next;
		ft_lstfree_node(&node);
		return ;
	}
	node = *list;
	while (node->next && index--)
	{
		previous = node;
		node =  node->next;
	}
	previous->next = node->next;
	node->next = NULL;
	ft_lstfree_node(&node);
}

int main(int arc, char **argv)
{
    char* line;
    t_list  *list;
    t_list  *current;

    list = NULL;
    ft_lstadd_in_index(&list, ft_lstnew(strdup("1")), 0);
    ft_lstadd_in_index(&list, ft_lstnew(strdup("2")), 0);
    ft_lstadd_in_index(&list, ft_lstnew(strdup("3")), 0);
    current = list;
    while (current)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
    printf("apply changes\n");
    ft_lstadd_in_index(&list, ft_lstnew(strdup("4")), 0);
    current = list;
    while (current)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
	printf("apply delete\n");
	ft_lstdelete_index(&list, 10);
	current = list;
    while (current)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
    return 0;
}
