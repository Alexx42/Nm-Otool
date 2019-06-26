/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process_otool.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:25:25 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 21:07:35 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

extern int g_idx;

void		launch_process_otool(t_map *file, t_arch *arch,
			t_header *header)
{
	get_arch(arch, file);
	if (get_header(file, arch, header))
		error_munmap("Invalid object file", file);
	if (!arch->is_fat && arch->is_64)
		process_header_64(file, arch, header->header_64);
	else if (!arch->is_fat && !arch->is_64 && !arch->is_archive)
		process_header_32(file, arch, header->header_32);
	else if (arch->is_archive)
		process_archive(file, arch, header);
	else if (arch->is_fat && arch->is_64)
		process_fat_header_64(file, arch, header);
	else if (arch->is_fat && !arch->is_64)
		process_fat_header_32(file, arch, header);
}

void		start_process_otool(char *filename, t_map *file)
{
	t_header	header;
	t_arch		arch;

	load_file(file, filename);
	launch_process_otool(file, &arch, &header);
	munmap(file->ptr, file->size);
	g_idx++;
}