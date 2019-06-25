/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:57:35 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 14:20:17 by ale-goff         ###   ########.fr       */
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
# include <ar.h>
# include "common.h"

# define IS_VALID_SYMBOL_TYPE(x) (x == N_SECT || x == N_ABS || x == N_INDR)
# define IS_TYPE(a, b, c, d) (!ft_strcmp(a, b) && !ft_strcmp(c, d))
# define SIZE 512

typedef struct s_map		t_map;

typedef struct				s_cpu_type_names
{
	cpu_type_t				cputype;
 	const char				*cpu_name;
}							t_cpu_type_names;

typedef struct				s_arch
{
	uint32_t				magic;
	uint8_t					is_64;
	uint8_t					is_big_endian;
	uint8_t					is_fat;
	uint8_t					is_archive;
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
	struct ar_hdr			*archive_header;
}							t_header;

void						load_file(t_map *file, char *ptr);
void						start_process_nm(char *path, t_map file);
void						launch_process(t_map *file, t_arch *arch,
							t_header *header);

void						get_arch(t_arch *arch, t_map *file);
int							get_header(t_map *file,
							t_arch *arch, t_header *header);

void						process_archive(t_map *file, t_arch *arch,
							t_header *header);
void						process_fat_header_64(t_map *file, t_arch *arch,
							t_header *header);
void						process_fat_header_32(t_map *file, t_arch *arch,
							t_header *header);
void						process_header_64(t_map *file, t_arch *arch,
							struct mach_header_64 *header);
void						process_header_32(t_map *file, t_arch *arch,
							struct mach_header *header);

void						parse_symbol_32(struct symtab_command *sym,
							t_map *file, t_arch *arch);
void						parse_symbol_64(struct symtab_command *sym,
							t_map *file, t_arch *arch);
void						parse_segment_64(struct segment_command_64 *segment,
							t_arch *arch, t_map *file);
void						parse_segment_32(struct segment_command *segment,
							t_arch *arch, t_map *file);

void						quicksort(t_symbol *symbol, uint32_t low,
							uint32_t right);
const char					*cpu_type_name(cpu_type_t cpu_type);
int							cpu_host(const char *cpu);
void						print_architecture(const char *cpu, char *filename);
t_info_sec					*get_section(void);
void						init_section(void);

#endif
