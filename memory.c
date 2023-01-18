/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:18:30 by mhedtman          #+#    #+#             */
/*   Updated: 2023/01/18 14:11:05 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_list(t_lst *list)
{
	int x = 0;
	printf("PRINT_LIST: \n");
	while (list)
	{
		printf("[%d] ", x);
		print3d("VECTOR IN LIST: ", *list->vec);
		// printf("HALO");
		// print_clr(*list->clr);
		x++;
		if (list->next)
			list = list->next;
		else
			break ;
	}
	x++;
}

t_lst	*mk_node(t_3d *v, t_clr *clr)
{
	t_lst	*new_node;

	new_node = (t_lst *)ft_calloc(1, sizeof(t_lst));
	if (!v && !clr)
	{
		new_node->clr = NULL;
		new_node->vec = NULL;
	}
	else if (!v && clr)
	{
		new_node->clr = clr;
		new_node->vec = NULL;
	}
	else if (v && !clr)
	{
		new_node->clr = NULL;
		new_node->vec = v;
	}
	new_node->next = NULL;
	return (new_node);
}

void	add_3d(t_lst **lst, t_3d *v)
{
	t_lst	*new_node;

	new_node = mk_node(v, NULL);
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new_node;
}

void	add_clr(t_lst **lst, t_clr *clr)
{
	t_lst	*new_node;

	new_node = mk_node(NULL, clr);
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new_node;	
}

	void	free_from_list(t_lst *lst)
{
	t_lst *temp;

	while(lst)
	{
		temp = lst->next;
		if (lst->clr)
			free(lst->clr);
		if (lst->vec)
			free(lst->vec);
		free(lst);
		lst = temp;		
	}
}

void	add_to_list(t_lst **lst, t_3d *v, t_clr *clr)
{
	if ((*lst)->clr == NULL && (*lst)->vec == NULL)
	{
		(*lst)->vec = v;
		return ;
	}
	if (!v)
		add_clr(lst, clr);
	else if (!clr)
		add_3d(lst, v);
}