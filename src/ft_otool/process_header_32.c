/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_header_32.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 13:34:07 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 20:37:32 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

extern int g_idx;
extern int g_fat;
extern int g_archive;

void		process_header_32(t_map *file, t_arch *arch,
			struct mach_header *header)
{
	uint32_t				i;
	struct load_command		*lc;
	int						offset;
	uint32_t				val;

	i = 0;
	val = should_swap_32(arch, header->ncmds);
	offset = sizeof_header(arch);
	lc = (void *)file->ptr + offset;
	if (!g_fat && !g_archive)
		print_file_otool(file->file[g_idx++]);
	while (i < val)
	{
		if (should_swap_32(arch, lc->cmd) == LC_SEGMENT)
			parse_segment_32((struct segment_command *)lc, arch, file);
		lc = (void *)lc + should_swap_32(arch, lc->cmdsize);
		error_out_of_memory(file, (void *)lc);
		i++;
	}
}
