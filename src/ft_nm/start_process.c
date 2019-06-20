/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:07:50 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 20:48:21 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>


// static void		process_fat(t_map *file, t_arch *arch, struct fat_header *header)
// {
	
// }

static void		print_output(struct symtab_command *sym, t_map *file)
{
	uint32_t				i;
	struct nlist_64			*el;
	t_symbol				*symbol;
	char					*strtable;

	i = -1;
	el = (void *)file->ptr + sym->symoff;
	strtable = file->ptr + sym->stroff;
	if ((symbol = malloc(sizeof(*symbol) * (sym->nsyms + 1))) == NULL)
		error_munmap("Malloc failed", file);
	while (++i < sym->nsyms)
		ft_strncpy(symbol[i].name, strtable + el[i].n_un.n_strx, SIZE);
	print_symbols(symbol, sym);
	free(symbol);
}

static void		process_small_header(t_map *file, t_arch *arch,
				struct mach_header_64 *header)
{
	uint32_t				i;
	struct load_command		*lc;
	int						offset;
	struct symtab_command	*sym;

	offset = sizeof_header(arch);
	lc = (void *)file->ptr + offset;
	i = -1;
	while (++i < header->ncmds)
	{
		if (arch->endianness)
			swap_load_command(lc, 0);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output(sym, file);
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void			start_process(char *path)
{
	t_map						file;
	t_arch						arch;
	t_header					header;

	load_file(&file, path);
	get_arch(&arch, &file);
	if (arch.endianness)
	{
		if (!arch.bit_arch)
			swap_mach_header(header.header_32, 0);
		else if (!arch.is_fat)
			swap_mach_header_64(header.header_64, 0);
		else
			swap_fat_header(header.fat_header, 0);
	}
	if (get_header(&file, &arch, &header))
		error_munmap("Malloc failed", &file);
	if (!arch.is_fat)
		process_small_header(&file, &arch, header.header_64);
	munmap(file.ptr, file.size);
}
