/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:07:55 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/20 00:20:37 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		symbols_type(t_symbol symbol)
{
	if (symbol.type == N_ABS || symbol.type == N_SECT || symbol.type == N_INDR)
		print_address(symbol.value, 16);
	if (symbol.type == N_SECT)
		write(1, " T ", 3);
}

void		print_symbols(t_symbol *symbol, struct symtab_command *sym)
{
	uint32_t		i;

	i = -1;
	while (++i < sym->nsyms)
	{
		if (!ft_strcmp(symbol[i].name, ""))
			continue ;
		if (symbol[i].type == N_UNDF && symbol[i].ext)
		{
			write(1, "                ", 16);
			write(1, " U ", 3);
		}
		else
		{
			symbols_type(symbol[i]);
		}
		write(1, symbol[i].name, ft_strlen(symbol[i].name));
		write(1, "\n", 1);
	}
}