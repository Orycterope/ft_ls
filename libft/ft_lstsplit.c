//header here

#include "libft.h"
/*
** Splits a list on the first non zero return of the cmp function
** and returns a pointer to the second list
** if the callback function never returned true, 
** or if the split is on the last element null is returned.
*/

t_list			*ft_lstsplit(t_list *lst, int (*cmp_func)(void*))
{
	t_list	*second;

	if (lst == NULL)
		return (lst);
	while (lst && (*cmp_func)(lst->content))
		lst = lst->next;
	if (lst == NULL)
		return (NULL);
	second = lst->next;
	lst->next = NULL;
	return (second);
}
