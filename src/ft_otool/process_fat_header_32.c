/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fat_header_32.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 14:06:00 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 23:48:38 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

extern int g_idx;
extern int g_count;
extern int g_fat;

static void					fat_launch_process(t_map *file,
							t_arch *arch, t_header *header,
							struct fat_arch *fat_arch)
{
	void				*tmp;

	tmp = file->ptr;
	file->ptr = file->ptr + should_swap_32(arch, fat_arch->offset);
	launch_process_otool(file, arch, header);
	file->ptr = tmp;
	g_count = 0;
}

void						process_fat_header_32(t_map *file,
							t_arch *arch, t_header *header)
{
	struct fat_arch		*fat_arch;
	uint32_t			val;
	uint32_t			i;
	const char			*cpu;

	i = -1;
	g_fat = 1;
	val = should_swap_32(arch, header->fat_header->nfat_arch);
	fat_arch = (struct fat_arch *)(header->fat_header + 1);
	while (++i < val)
	{
		if (val > 1 && !i &&
		cpu_host(cpu_type_name(should_swap_32(arch, fat_arch[i + 1].cputype))))
			continue ;
		cpu = cpu_type_name(should_swap_32(arch, fat_arch[i].cputype));
		val > 1 && !cpu_host(cpu) ?
		print_architecture_otool(cpu, file->file[g_idx]) : 0;
		fat_launch_process(file, arch, header, &fat_arch[i]);
		if (cpu_host(cpu))
			break ;
	}
	g_fat = 0;
}
