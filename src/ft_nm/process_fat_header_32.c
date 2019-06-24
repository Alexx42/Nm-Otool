/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fat_header_32.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 14:06:00 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/24 01:16:54 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

extern int g_idx;

void						process_fat_header_32(t_map *file,
							t_arch *arch, t_header *header)
{
	struct fat_arch		*fat_arch;
	struct fat_header	*fat_header;
	uint32_t			val;
	uint32_t			i;
	const char			*cpu;
	void				*tmp;

	i = 0;
	fat_header = header->fat_header;
	val = should_swap_32(arch, fat_header->nfat_arch);
	fat_arch = (struct fat_arch *)(fat_header + 1);
	while (i < val)
	{
		fat_arch = (void *)file->ptr + sizeof(struct fat_header) +
		(i * sizeof(struct fat_arch));
		cpu = cpu_type_name(should_swap_32(arch, fat_arch->cputype));
		if (!ft_strcmp(cpu, "unknown"))
			return ;
		print_architecture(cpu, file->file[g_idx]);
		printf("offset = %d\n", should_swap_32(arch, fat_arch->offset));
		tmp = file->ptr;
		file->ptr = file->ptr + should_swap_32(arch, fat_arch->offset);
		// launch_process(file, arch, header);
		file->ptr = tmp;
		i++;
	}
}
