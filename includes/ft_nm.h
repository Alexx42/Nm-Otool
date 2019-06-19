/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:57:35 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/18 23:52:12 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdlib.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/swap.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>

# define MACH_HEADER_64 sizeof(mach_header_64)
# define MACH_HEADER_32 sizeof(mach_header_32)

# include "common.h"

typedef struct				s_map
{
	char					*ptr;
	off_t					size;
}							t_map;

typedef struct				s_arch
{
	uint32_t				magic;
	uint8_t					bit_arch;
	uint8_t					endianness;
	uint8_t					is_fat;
}							t_arch;

typedef struct				s_header
{
	struct mach_header_64	*header_64;
	struct mach_header		*header_32;
	struct fat_header		*fat_header;
}							t_header;

void						load_file(t_map *file, char *ptr);
void						start_process(char *path);

void						get_arch(char *ptr, t_arch *arch);
int							get_header(t_map *file,
							t_arch *arch, t_header *header);

#endif
