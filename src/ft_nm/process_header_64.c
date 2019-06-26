/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_header_64.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:28:36 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 21:59:20 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

extern int	g_idx;
extern int	g_fat;
extern int	g_archive;

void		process_header_64(t_map *file, t_arch *arch,
				struct mach_header_64 *header)
{
	uint32_t				i;
	struct load_command		*lc;
	uint32_t				val;

	i = -1;
	val = should_swap_32(arch, header->ncmds);
	lc = (void *)file->ptr + sizeof(struct mach_header_64);
	if (file->mul_files && !g_fat && !g_archive)
		print_file(file->file[g_idx]);
	while (++i < val)
	{
		if (should_swap_32(arch, lc->cmd) == LC_SEGMENT_64)
			parse_segment_64((struct segment_command_64 *)lc, arch, file);
		else if (should_swap_32(arch, lc->cmd) == LC_SYMTAB)
			parse_symbol_64((struct symtab_command *)lc, file, arch);
		lc = (void *)lc + lc->cmdsize;
		error_out_of_memory(file, lc);
	}
}
