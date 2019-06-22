/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:07:55 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/21 21:07:54 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static void		symbols_type(t_symbol symbol)
{
	if (symbol.type == N_ABS || symbol.type == N_INDR || symbol.type == N_SECT)
		print_address(symbol.value, 16);
	if (symbol.type == N_ABS)
		write(1, symbol.ext ? " A " : " a ", 3);
	if (symbol.type == N_SECT)
	{
		if (get_section()->bss == symbol.sect)
			write(1, symbol.ext ? " B " : " b ", 3);
		else if (get_section()->data == symbol.sect)
			write(1, symbol.ext ? " D " : " d ", 3);
		else if (get_section()->text == symbol.sect)
			write(1, symbol.ext ? " T " : " t ", 3);
		else
			write(1, symbol.ext ? " S " : " s ", 3);
	}
}

static void		print_symbols(t_symbol *symbol,
				struct symtab_command *sym)
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
		if (IS_VALID_SYMBOL_TYPE(symbol[i].type) ||
		(symbol[i].type == N_UNDF && symbol[i].ext))
		{
			ft_putendl(symbol[i].name);
		}
	}
}

static void		add_symbol(t_symbol *sym, struct nlist_64 *el, char *strtable)
{
	ft_strncpy((*sym).name, strtable + (*el).n_un.n_strx, SIZE);
	(*sym).type = (*el).n_type & N_TYPE;
	(*sym).ext = (*el).n_type & N_EXT;
	(*sym).value = (*el).n_value;
	(*sym).sect = (*el).n_sect;
}

void			parse_symbol(struct symtab_command *sym,
				t_map *file, t_arch *arch)
{
	uint32_t				i;
	struct nlist_64			*el;
	t_symbol				*symbol;
	char					*strtable;

	i = -1;
	el = (void *)file->ptr + sym->symoff;
	strtable = file->ptr + sym->stroff;
	if ((symbol = malloc(sizeof(*symbol) * (sym->nsyms))) == NULL)
		error_munmap("Malloc failed", file);
	if (arch->is_big_endian)
		swap_symtab_command(sym, 0);
	while (++i < sym->nsyms)
		add_symbol(&symbol[i], &el[i], strtable);
	quicksort(symbol, 0, sym->nsyms - 1);
	print_symbols(symbol, sym);
	free(symbol);
}
