/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:00:36 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/24 19:27:32 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		get_arch(t_arch *arch, t_map *file)
{
	arch->magic = *(int *)file->ptr;
	if (!is_valid_magic(arch->magic, file->ptr))
		error_munmap("The file was not recognized as a valid object file",
		file);
	arch->is_64 = IS_64_OBJ(arch->magic) || IS_64_FAT(arch->magic);
	arch->is_fat = IS_FAT_LITTLE(arch->magic) || IS_FAT_BIG(arch->magic);
	arch->is_archive = IS_ARCHIVE(file->ptr);
	arch->is_big_endian = IS_BIG_OBJ(arch->magic) || IS_FAT_BIG(arch->magic);
}
