/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:07:50 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/24 00:17:41 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

extern int g_idx;

void		launch_process(t_map *file, t_arch *arch, t_header *header)
{
	get_arch(arch, file);
	if (get_header(file, arch, header))
		error_munmap("Malloc failed", file);
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

void			start_process(char *path, t_map file)
{
	t_arch						arch;
	t_header					header;

	init_section();
	load_file(&file, path);
	launch_process(&file, &arch, &header);
	munmap(file.ptr, file.size);
}
