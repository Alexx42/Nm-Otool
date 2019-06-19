/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:07:50 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 12:11:06 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>


// static void		process_fat(t_map *file, t_arch *arch, struct fat_header *header)
// {
	
// }

static void		print_output(struct load_command *lc, t_map *file)
{
	struct symtab_command	*sym;
	uint32_t				i;
	struct nlist_64			*el;

	sym = (struct symtab_command *)lc;
	el = (void *)file->ptr + sym->symoff;
	i = -1;
	while (++i < sym->nsyms)
	{
		printf("%s\n", (file->ptr + sym->stroff) + el[i].n_un.n_strx);
	}
}

static void		process_header(t_map *file, t_arch *arch, struct mach_header_64 *header)
{
	uint32_t				i;
	struct load_command		*lc;
	int						offset;

	offset = sizeof_header(arch);
	lc = (void *)file->ptr + offset;
	i = -1;
	while (++i < header->ncmds)
	{
		if (arch->endianness)
			swap_load_command(lc, 0);
		if (lc->cmd == LC_SYMTAB)
		{
			print_output(lc, file);
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
		process_header(&file, &arch, header.header_64);
	// else
	// 	process_fat(&file, &arch, header.fat_header);
	munmap(file.ptr, file.size);
}
