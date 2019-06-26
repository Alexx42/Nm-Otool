/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 00:22:54 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 17:36:29 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static void	swap(t_symbol *a, t_symbol *b)
{
	t_symbol tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition_nm(t_symbol *symbol, uint32_t low, uint32_t high)
{
	t_symbol	pivot;
	int			i;
	uint32_t	j;

	pivot = symbol[high];
	i = low - 1;
	j = low - 1;
	while (++j <= high - 1)
	{
		if (ft_strcmp(symbol[j].name, pivot.name) < 0 ||
			(!ft_strcmp(symbol[j].name, pivot.name) &&
			symbol[j].value <= pivot.value))
		{
			i++;
			swap(&symbol[i], &symbol[j]);
		}
	}
	swap(&symbol[i + 1], &symbol[high]);
	return (i + 1);
}

static int	partition_otool(t_symbol *symbol, uint32_t low, uint32_t high)
{
	t_symbol	pivot;
	int			i;
	uint32_t	j;

	pivot = symbol[high];
	i = low - 1;
	j = low - 1;
	while (++j <= high - 1)
	{
		if (symbol[j].value <= pivot.value)
		{
			i++;
			swap(&symbol[i], &symbol[j]);
		}
	}
	swap(&symbol[i + 1], &symbol[high]);
	return (i + 1);
}

void		quicksort(t_symbol *symbol, uint32_t low, uint32_t high, int type)
{
	int			pi;

	if ((int)low < (int)high)
	{
		if (type)
			pi = partition_nm(symbol, low, high);
		else
			pi = partition_otool(symbol, low, high);
		if (pi < 0)
			return ;
		quicksort(symbol, low, pi - 1, type);
		quicksort(symbol, pi + 1, high, type);
	}
}
