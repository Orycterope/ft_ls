#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list	*i;
	
	if (new == NULL)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		i = *alst;
		while (i->next)
			i = i->next;
		i->next = new;
	}
}
