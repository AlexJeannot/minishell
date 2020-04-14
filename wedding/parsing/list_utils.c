#include "../includes/parsing.h"

void		print_lst(void)
{
	int 	i;

	printf("=================\n");
	printf("cmd:[%s]\n", lst->cmd);
	printf("arg:");
	i = 0;
	while (lst->arg[i])
	{
		printf("[%s]", lst->arg[i]);
		i++;
	}
	printf("\nraw:");
	i = 0;
	while (lst->raw[i])
	{
		printf("[%s]", lst->raw[i]);
		i++;
	}
	printf("\n=================\n");
}

//void		print_lst(void)
//{
//	t_list *tmp;
//	int 	i;
//	int		j;
//	int 	k;
//
//	tmp = lst;
//	j = 0;
//	while (tmp)
//	{
//		printf("=================\n");
//		printf("[%d]\n", j++);
//		printf("cmd:[%s]\n", tmp->cmd);
//		printf("arg:");
//		i = 0;
//		while (tmp->arg[i])
//		{
//			printf("[%s]", tmp->arg[i]);
//			i++;
//		}
//		printf("\n");
//		if (tmp->rdo_filetab)
//		{
//			printf("rdo_filetab: ");
//			i = 0;
//			while (tmp->rdo_filetab[i])
//			{
//				printf("[%s]", tmp->rdo_filetab[i]);
//				i++;
//			}
//		}
//		printf("\n");
//		printf("rdo_filename:[%s]\n", tmp->rdo_filename);
//		printf("rdo_type:[%d]\n", tmp->rdo_type);
//		if (tmp->rdc_filetab)
//		{
//			printf("rdc_filetab: ");
//			i = 0;
//			while (tmp->rdc_filetab[i])
//			{
//				printf("[%s]", tmp->rdc_filetab[i]);
//				i++;
//			}
//		}
//		printf("\n");
//		printf("rdc_filename:[%s]\n", tmp->rdc_filename);
//		printf("rdc_type:[%d]\n", tmp->rdc_type);
//	  printf("(%d)\n", tmp->pipe);
//		k = 0;
//		printf("rdc_index : ");
//		while (tmp->rdc_index[k] != -1)
//		{
//			printf("[%d] ", tmp->rdc_index[k]);
//			k++;
//		}
//		printf("\n");
//		k = 0;
//		printf("rdo_index : ");
//		while (tmp->rdo_index[k] != -1)
//		{
//			printf("[%d] ", tmp->rdo_index[k]);
//			k++;
//		}
//		printf("=================\n");
//		tmp = tmp->next;
//	}
//}

//void		print_lst(void)
//{
//	t_list *tmp;
//	int 	i;
////	int		j;
//
//	tmp = lst;
//	//j = 0;
//	while (tmp)
//	{
//		//printf("\n[%d]", j++);
//		//printf("cmd:%s}", tmp->cmd);
//		i = 0;
//		while (tmp->arg[i])
//		{
//			printf("%s", tmp->arg[i]);
//			//printf(".%s", tmp->arg[i]);
//			i++;
//		}
//		//printf("(%d)\n", tmp->pipe);
//		tmp = tmp->next;
//	}
//	printf("\n");
//}

t_list	*new_lst(void)
{
	return (NULL);
}

bool		is_empty_lst()
{
	if (!lst)
		return (true);
	return (false);
}

int	is_valid(char *stock)
{
	int i;

	i = 0;
	while (stock[i])
	{
		if (stock[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	del_first(void)
{
	t_list *elem;

	if (is_empty_lst())
		lst = new_lst();
	if (!(elem = malloc(sizeof(t_list))))
		ft_exit("malloc failed", 1);

	elem = lst->next;
	free(lst);
	lst = elem;
}

void	clear_lst()
{
	if (is_empty_lst())
		new_lst();
	else
		while (lst)
			del_first();
}
