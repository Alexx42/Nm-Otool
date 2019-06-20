/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:07:55 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 20:42:50 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		print_symbols(t_symbol *symbol, struct symtab_command *sym)
{
	uint32_t		i;

	i = -1;
	while (++i < sym->nsyms)
	{
		printf("sym name = %s\n", symbol[i].name);
	}
}