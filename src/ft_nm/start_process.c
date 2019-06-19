/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:07:50 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 00:27:53 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>


// static void		process_fat(t_map *file, t_arch *arch, struct fat_header *header)
// {
	
// }

static void		process_header(t_map *file, t_arch *arch, void *header)
{
	int						i;
	struct load_command		*lc;
	int						offset;

	offset = sizeof_header(header);
	lc = (void *)file->ptr + offset;
	i = 0;
	(void)arch;
	while (i < (struct mach_header_64 *)header)
	{
		i++;
	}
}

void			start_process(char *path)
{
	t_map						file;
	t_arch						arch;
	t_header					header;

	load_file(&file, path);
	get_arch(file.ptr, &arch);
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
	if (!arch.is_fat)
		process_header(&file, &arch, &header);
	// else
	// 	process_fat(&file, &arch, header.fat_header);
	munmap(file.ptr, file.size);
}
