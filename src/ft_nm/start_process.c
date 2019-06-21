/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:07:50 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/21 00:21:45 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

uint8_t		g_idx = 0;

static void		process_header_64(t_map *file, t_arch *arch,
				struct mach_header_64 *header)
{
	uint32_t				i;
	struct load_command		*lc;
	int						offset;

	offset = sizeof_header(arch);
	lc = (void *)file->ptr + offset;
	i = -1;
	if (arch->endianness)
		swap_load_command(lc, 0);
	init_section();
	write(1, "\n", 1);
	ft_putendl(file->file[g_idx++]);
	while (++i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			parse_segment((struct segment_command_64 *)lc, arch);
		}
		else if (lc->cmd == LC_SYMTAB)
		{
			parse_symbol((struct symtab_command *)lc, file, arch);
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void			start_process(char *path, t_map file)
{
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
	if (!arch.is_fat && arch.bit_arch)
		process_header_64(&file, &arch, header.header_64);
	else if (!arch.is_fat && !arch.bit_arch)
		;
	else if (arch.is_fat)
		;
	munmap(file.ptr, file.size);
}
