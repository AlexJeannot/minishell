#include <stdio.h>
#include "minishell.h"

static t_list *new_lst(void)
{
	return (NULL);
}

static bool is_empty_lst(t_list *lst)
{
	if (!lst)
		return (true);
	return (false);
}

static int	lst_size(t_list *lst)
{
	int size;

	size = 0;
	if (!is_empty_lst(lst))
	{
		while (lst)
		{
			size++;
			lst = lst->next;
		}
	}
	return (size);
}

static void	print_lst(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", lst->cmd);
		lst = lst->next;
	}
}

static t_list *add_back(t_list *lst, char *x)
{
	t_list *elem;	
	t_list *tmp;

	if (!(elem = malloc(sizeof(t_list))))
		exit(1);
	elem->cmd = x;
	elem->next = NULL;

	if (is_empty_lst(lst))
		return (elem);

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = elem;
	return (lst);
}

static t_list *add_front(t_list *lst, char *x)
{
	t_list *elem;

	if (!(elem = malloc(sizeof(t_list))))
		exit(1);
	elem->cmd = x;
	
	if (is_empty_lst(lst))
		elem->next = NULL;
	else
		elem->next = lst;
	return (elem);
}

static t_list	*del_last(t_list *lst)
{
	t_list *tmp;
	t_list *bf;

	if (is_empty_lst(lst))
		return (new_lst());
	if (!lst->next)
	{
		free(lst);
		lst = NULL;
		return (new_lst());
	}
	tmp = lst;
	while (tmp->next)
	{
		bf = tmp;
		tmp = tmp->next;
	}
	bf->next = NULL; 
	free(tmp);
	tmp = NULL;
	return (lst);
}

static t_list *del_first(t_list *lst)
{
	t_list *elem;

	if (is_empty_lst(lst))
		return (new_lst());
	if (!(elem = malloc(sizeof(t_list))))
		exit(1);
	elem = lst->next;
	free(lst);
	lst = NULL;
	return (elem);
}

static void	*clear_lst(t_list *lst)
{
	if (is_empty_lst(lst))
		return (new_lst());
	while (lst)
		lst = del_first(lst);
	return (lst);
}

int main()
{
	t_list *lst;

	lst = new_lst();
	lst = add_front(lst, "bonjour");
	lst = add_back(lst, "je");
	lst = add_back(lst, "suis");
	lst = add_back(lst, "heureux");
	lst = del_last(lst);
	lst = del_first(lst);
	lst = clear_lst(lst);
	if (is_empty_lst(lst))
		printf("@\n");
	printf("[%d]\n", lst_size(lst));
	print_lst(lst);
	return (0);
}
