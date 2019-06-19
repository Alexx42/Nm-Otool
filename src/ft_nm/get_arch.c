/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:00:36 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 11:53:16 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		get_arch(t_arch *arch, t_map *file)
{
	arch->magic = *(int *)file->ptr;
	if (!is_valid_magic(arch->magic))
		error_munmap("The file was not recognized as a valid object file", file);
	arch->endianness = get_endianess(arch->magic);
	arch->bit_arch = get_magic_bit(arch->magic);
	arch->is_fat = get_fat(arch->magic);
}