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

void	clear_lst_content(void)
{
	t_list *tmp;
	int	i;

	tmp = lst;
	while (lst)
	{
		i = 0;
		while (lst->raw[i])
			free(lst->raw[i++]);
		i = 0;
		while (lst->arg[i])
			free(lst->arg[i++]);
		i = 0;
		if (lst->rdc_filetab)
			while (lst->rdc_filetab[i])
				free(lst->rdc_filetab[i++]);
		i = 0;
		if (lst->rdo_filetab)
			while (lst->rdo_filetab[i])
				free(lst->rdo_filetab[i++]);
  		if (lst->rdc_index)
  			free(lst->rdc_index);
  		if (lst->rdo_index)
  			free(lst->rdo_index);
  		if (lst->cmd)
  			free(lst->cmd);
		if (lst->rdc_filename)
			free(lst->rdc_filename);
		if (lst->rdo_filename)
			free(lst->rdo_filename);
		lst = lst->next;
	}
	lst = tmp;
}

void	clear_lst()
{
	t_list *tmp;

	if (is_empty_lst())
		new_lst();
	else
		while (lst)
		{
			tmp = lst;
			lst = lst->next;
			free(tmp);
		}
	free(lst);
}

void	free_lst(void)
{
	clear_lst_content();
	clear_lst();
}

