/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_header_64.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:28:36 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 16:18:38 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int			g_idx = 0;
extern int	g_fat;
extern int	g_archive;

void		process_header_64(t_map *file, t_arch *arch,
				struct mach_header_64 *header)
{
	uint32_t				i;
	struct load_command		*lc;
	int						offset;

	i = 0;
	offset = sizeof_header(arch);
	lc = (void *)file->ptr + offset;
	if (arch->is_big_endian)
		swap_load_command(lc, 0);
	if (file->mul_files && !g_fat && !g_archive)
		print_file(file->file[g_idx]);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			parse_segment_64((struct segment_command_64 *)lc, arch, file);
		else if (lc->cmd == LC_SYMTAB)
			parse_symbol_64((struct symtab_command *)lc, file, arch);
		lc = (void *)lc + lc->cmdsize;
		error_out_of_memory(file, lc);
		i++;
	}
}
