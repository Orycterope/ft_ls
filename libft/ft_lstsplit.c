//header here

#include "libft.h"
/*
** Splits a list everytime the cmp function returns a non-zero value
** and returns a list of all the sublists created.
** If the callback function never returned true, null is returned
** and the list is left as is.
*/

t_list			*ft_lstsplit(t_list *lst, int (*cmp_func)(void*))
{
	t_list	*parent_lst;
	t_list	*previous;

	if (lst == NULL)
		return (NULL);
	parent_lst = NULL;
	previous = NULL;
	while (lst)
	{
		if ((*cmp_func)(lst->content))
		{
			if (previous == NULL)
				ft_lstappend(&parent_lst, 
					ft_lstnew_nocpy(NULL, sizeof(void*)));
			else
				ft_lstappend(&parent_lst, 
					ft_lstnew_nocpy(lst->content, sizeof(void*)));
			if (previous)
				previous->next = NULL;
		}
		previous = lst;
		lst = lst->next;
	}
	return (parent_lst);
}
