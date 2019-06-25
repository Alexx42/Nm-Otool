/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fat_header_64.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 00:52:54 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/24 19:25:16 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

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
	launch_process(file, arch, header);
	file->ptr = tmp;
	g_count = 0;
}

void						process_fat_header_64(t_map *file,
							t_arch *arch, t_header *header)
{
	struct fat_arch		*fat_arch;
	uint32_t			val;
	uint32_t			i;
	const char			*cpu;

	i = -1;
	g_fat = 1;
	val = should_swap_64(arch, header->fat_header->nfat_arch);
	while (++i < val)
	{
		fat_arch = ((void *)file->ptr + sizeof(struct fat_header)) +
		(i * sizeof(struct fat_arch));
		cpu = cpu_type_name(should_swap_64(arch, fat_arch->cputype));
		if (!ft_strcmp(cpu, "unknown"))
			error_munmap("Invalid cpu type", file);
		val > 1 && !cpu_host(cpu) ?
		print_architecture(cpu, file->file[g_idx]) : 0;
		fat_launch_process(file, arch, header, fat_arch);
		if (cpu_host(cpu))
			break ;
	}
	g_fat = 0;
	g_idx++;
}
