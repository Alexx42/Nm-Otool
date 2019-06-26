/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:48:28 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/26 13:01:05 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <ft_nm.h>
# define HEX "0123456789abcdef"
# define IS_ARCHIVE(x) (!ft_strncmp(x, ARMAG, SARMAG))
# define IS_64_OBJ(x) (x == MH_MAGIC_64 || x == MH_CIGAM_64)
# define IS_32_OBJ(x) (x == MH_MAGIC || x == MH_CIGAM)
# define IS_64_FAT(x) (x == FAT_MAGIC_64 || x == FAT_CIGAM_64)
# define IS_BIG_OBJ(x)(x == MH_CIGAM || x == MH_CIGAM_64)
# define IS_FAT_LITTLE(x) (x == FAT_MAGIC || x == FAT_MAGIC_64)
# define IS_FAT_BIG(x) (x == FAT_CIGAM || x == FAT_CIGAM_64)
# define IS_VALID_SYMBOL_TYPE(x) (x == N_SECT || x == N_ABS || x == N_INDR)
# define IS_TYPE(a, b, c, d) (!ft_strcmp(a, b) && !ft_strcmp(c, d))

typedef struct s_symbol		t_symbol;

typedef struct				s_header
{
	struct mach_header_64	*header_64;
	struct mach_header		*header_32;
	struct fat_header		*fat_header;
	struct ar_hdr			*archive_header;
}							t_header;
# pragma pack(4)

typedef struct				s_map
{
	char					*ptr;
	off_t					size;
	char					**file;
	uint8_t					mul_files;
	void					*max_size;
}							t_map;

typedef struct				s_arch
{
	uint8_t					is_64;
	uint8_t					is_big_endian;
	uint8_t					is_fat;
	uint8_t					is_archive;
	uint32_t				magic;
}							t_arch;

typedef struct				s_info_sec
{
	uint8_t					text;
	uint8_t					data;
	uint8_t					bss;
}							t_info_sec;

typedef struct				s_cpu_type_names
{
	cpu_type_t				cputype;
	const char				*cpu_name;
}							t_cpu_type_names;

void						send_error(char *message);
void						error_munmap(char *message, t_map *file);
void						error_out_of_memory(t_map *file, void *ptr);
uint32_t					swap_32(uint32_t value);
uint64_t					swap_64(uint64_t value);
uint32_t					should_swap_32(t_arch *arch, uint32_t value);
uint64_t					should_swap_64(t_arch *arch, uint64_t value);
size_t						sizeof_header(t_arch *arch);
uint8_t						is_valid_magic(uint32_t magic, char *ptr);
void						print_address(size_t value, int length);
void						print_file(char *file);
void						get_arch(t_arch *arch, t_map *file);
int							get_header(t_map *file,
							t_arch *arch, t_header *header);
void						process_fat_header_64(t_map *file, t_arch *arch,
							t_header *header);
void						process_fat_header_32(t_map *file, t_arch *arch,
							t_header *header);
void						process_header_64(t_map *file, t_arch *arch,
							struct mach_header_64 *header);
void						process_header_32(t_map *file, t_arch *arch,
							struct mach_header *header);
void						process_archive(t_map *file, t_arch *arch,
							t_header *header);
void						load_file(t_map *file, char *ptr);
void						parse_symbol_32(struct symtab_command *sym,
							t_map *file, t_arch *arch);
void						parse_symbol_64(struct symtab_command *sym,
							t_map *file, t_arch *arch);
void						parse_segment_64(struct segment_command_64 *segment,
							t_arch *arch, t_map *file);
void						parse_segment_32(struct segment_command *segment,
							t_arch *arch, t_map *file);

void						quicksort(t_symbol *symbol, uint32_t low,
							uint32_t right, int type);
const char					*cpu_type_name(cpu_type_t cpu_type);
int							cpu_host(const char *cpu);
void						print_architecture(const char *cpu, char *filename);
t_info_sec					*get_section(void);
void						init_section(void);
void						print_architecture_otool(const char *cpu,
							char *filename);

#endif
