/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 00:52:54 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/21 19:58:06 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		process_fat_header(t_map *file, t_arch *arch, struct fat_header *header)
{
	(void)file;
	(void)arch;
	(void)header;
	printf("IM FAT\n");
}