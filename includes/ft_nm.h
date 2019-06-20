/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:57:35 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 20:30:37 by ale-goff         ###   ########.fr       */
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
# include "common.h"

# define SIZE 512

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

typedef struct				s_symbol
{
	char					name[SIZE];
}							t_symbol;

typedef struct				s_header
{
	struct mach_header_64	*header_64;
	struct mach_header		*header_32;
	struct fat_header		*fat_header;
}							t_header;

void						load_file(t_map *file, char *ptr);
void						start_process(char *path);

void						get_arch(t_arch *arch, t_map *file);
int							get_header(t_map *file,
							t_arch *arch, t_header *header);
void						print_symbols(t_symbol *symbol,
							struct symtab_command *sym);

#endif
