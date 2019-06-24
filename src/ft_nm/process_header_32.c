/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_header_32.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 13:34:07 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/23 22:48:22 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

extern int g_idx;

void		process_header_32(t_map *file, t_arch *arch,
			struct mach_header *header)
{
	uint32_t				i;
	struct load_command		*lc;
	int						offset;

	i = 0;
	offset = sizeof_header(arch);
	lc = (void *)file->ptr + offset;
	if (file->mul_files)
		print_file(file->file[g_idx++]);
	while (i < should_swap_32(arch, header->ncmds))
	{
		if (should_swap_32(arch, lc->cmd) == LC_SEGMENT)
			parse_segment_32((struct segment_command *)lc, arch);
		else if (should_swap_32(arch, lc->cmd) == LC_SYMTAB)
			parse_symbol_32((struct symtab_command *)lc, file, arch);
		lc = (void *)lc + should_swap_32(arch, lc->cmdsize);
		i++;
	}
}