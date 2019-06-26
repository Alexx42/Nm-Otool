/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_nm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 17:23:27 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/26 13:20:17 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static void		symbols_type(t_symbol symbol, t_arch *arch)
{
	if (arch->is_64)
		print_address(symbol.value, 16);
	else if (symbol.type)
		print_address(symbol.value, 8);
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

static void		print_indirect(t_symbol *symbol)
{
	ft_putstr(symbol->name);
	ft_putstr(" (indirect for ");
	ft_putstr(symbol->name);
	ft_putendl(")");
}

static void		print_symbols(t_symbol *symbol,
				uint32_t nsyms, t_arch *arch)
{
	uint32_t		i;

	i = -1;
	while (++i < nsyms)
	{
		if (*symbol[i].name == '\0')
			continue ;
		if ((symbol[i].type == N_UNDF && symbol[i].ext) ||
		symbol[i].type == N_INDR)
		{
			write(1, "                ", arch->is_64 ? 16 : 8);
			write(1, symbol[i].type == N_UNDF ? " U " : " I ", 3);
		}
		if (IS_VALID_SYMBOL_TYPE(symbol[i].type) ||
		(symbol[i].type == N_UNDF && symbol[i].ext))
		{
			if (symbol[i].type != N_UNDF && symbol[i].type != N_INDR)
				symbols_type(symbol[i], arch);
			if (symbol[i].type == N_INDR)
				print_indirect(&symbol[i]);
			else
				ft_putendl(symbol[i].name);
		}
	}
}

void			parse_symbol_32(struct symtab_command *sym,
				t_map *file, t_arch *arch)
{
	uint32_t				i;
	struct nlist			*el;
	t_symbol				*symbol;
	char					*strtable;
	uint32_t				val;

	i = -1;
	val = should_swap_32(arch, sym->nsyms);
	el = (void *)file->ptr + should_swap_32(arch, sym->symoff);
	strtable = file->ptr + should_swap_32(arch, sym->stroff);
	if ((symbol = malloc(sizeof(*symbol) * (val))) == NULL)
		error_munmap("Malloc failed", file);
	while (++i < val)
	{
		error_out_of_memory(file, el + i);
		symbol[i].name = strtable + should_swap_32(arch, el[i].n_un.n_strx);
		error_out_of_memory(file, symbol[i].name);
		symbol[i].type = el[i].n_type & N_TYPE;
		symbol[i].ext = el[i].n_type & N_EXT;
		symbol[i].value = should_swap_32(arch, el[i].n_value);
		symbol[i].sect = el[i].n_sect;
	}
	quicksort(symbol, 0, val - 1, 1);
	print_symbols(symbol, val, arch);
	free(symbol);
}

void			parse_symbol_64(struct symtab_command *sym,
				t_map *file, t_arch *arch)
{
	uint32_t				i;
	struct nlist_64			*el;
	t_symbol				*symbol;
	char					*strtable;
	uint32_t				val;

	i = -1;
	val = should_swap_64(arch, sym->nsyms);
	el = (void *)file->ptr + should_swap_64(arch, sym->symoff);
	strtable = file->ptr + should_swap_64(arch, sym->stroff);
	if ((symbol = malloc(sizeof(*symbol) * (val))) == NULL)
		error_munmap("Malloc failed", file);
	while (++i < val)
	{
		error_out_of_memory(file, el + i);
		symbol[i].name = strtable + should_swap_64(arch, el[i].n_un.n_strx);
		error_out_of_memory(file, symbol[i].name);
		symbol[i].type = el[i].n_type & N_TYPE;
		symbol[i].ext = el[i].n_type & N_EXT;
		symbol[i].value = should_swap_64(arch, el[i].n_value);
		symbol[i].sect = el[i].n_sect;
	}
	quicksort(symbol, 0, sym->nsyms - 1, 1);
	print_symbols(symbol, val, arch);
	free(symbol);
}
