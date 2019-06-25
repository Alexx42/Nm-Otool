/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:48:28 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 14:16:24 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

#include <ft_nm.h>
# define HEX "0123456789abcdef"
# define IS_ARCHIVE(x) (!ft_strncmp(x, ARMAG, SARMAG))
# define IS_64_OBJ(x) (x == MH_MAGIC_64 || x == MH_CIGAM_64)
# define IS_32_OBJ(x) (x == MH_MAGIC || x == MH_CIGAM)
# define IS_64_FAT(x) (x == FAT_MAGIC_64 || x == FAT_CIGAM_64)
# define IS_BIG_OBJ(x)(x == MH_CIGAM || x == MH_CIGAM_64)
# define IS_FAT_LITTLE(x) (x == FAT_MAGIC || x == FAT_MAGIC_64)
# define IS_FAT_BIG(x) (x == FAT_CIGAM || x == FAT_CIGAM_64)

typedef struct s_header t_header;
typedef struct s_arch	t_arch;

typedef struct				s_map
{
	char					*ptr;
	off_t					size;
	char					**file;
	uint8_t					mul_files;
	void					*max_size;
}							t_map;


void					send_error(char *message);
void					error_munmap(char *message, t_map *file);
void					error_out_of_memory(t_map *file, void *ptr);
uint32_t				swap_32(uint32_t value);
uint64_t				swap_64(uint64_t value);
uint32_t				should_swap_32(t_arch *arch, uint32_t value);
uint64_t				should_swap_64(t_arch *arch, uint64_t value);
size_t					sizeof_header(t_arch *arch);
uint8_t					is_valid_magic(uint32_t magic, char *ptr);
void					print_address(size_t value, int length);
void					print_file(char *file);

# endif
