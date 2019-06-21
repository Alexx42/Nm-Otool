/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:57:35 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/21 00:20:55 by ale-goff         ###   ########.fr       */
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

# define SIZE 128

typedef struct				s_map
{
	char					*ptr;
	off_t					size;
	char					**file;
}							t_map;

typedef struct				s_arch
{
	uint32_t				magic;
	uint8_t					bit_arch;
	uint8_t					endianness;
	uint8_t					is_fat;
}							t_arch;

typedef struct				s_info_sec
{
	uint8_t					text;
	uint8_t					data;
	uint8_t					bss;
}							t_info_sec;

typedef struct				s_symbol
{
	char					name[SIZE];
	uint32_t				type;
	uint32_t				ext;
	size_t					value;
	uint32_t				sect;
}							t_symbol;

typedef struct				s_header
{
	struct mach_header_64	*header_64;
	struct mach_header		*header_32;
	struct fat_header		*fat_header;
}							t_header;

void						load_file(t_map *file, char *ptr);
void						start_process(char *path, t_map file);

void						get_arch(t_arch *arch, t_map *file);
int							get_header(t_map *file,
							t_arch *arch, t_header *header);

void						parse_symbol(struct symtab_command *sym,
							t_map *file, t_arch *arch);
void						parse_segment(struct segment_command_64 *segment,
							t_arch *arch);

void						quicksort(t_symbol *symbol, uint32_t low,
							uint32_t right);

t_info_sec					*get_section(void);
void						init_section(void);

#endif
