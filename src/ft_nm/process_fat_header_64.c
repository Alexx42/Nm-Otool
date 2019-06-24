/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fat_header_64.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 00:52:54 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/22 14:28:41 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		process_fat_header_64(t_map *file, t_arch *arch, t_header *header)
{
	struct fat_header		*fat;

	fat = header->fat_header;
	(void)file;
	(void)arch;
	// if (arch->is_big_endian)
	// 	swap_64(fat->nfat_arch);
	// printf("%x\n", fat->nfat_arch);
}