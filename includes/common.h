/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:48:28 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 00:24:08 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

#include <ft_nm.h>

typedef struct s_map	t_map;
typedef struct s_header t_header;

void					send_error(char *message);
void					error_munmap(char *message, t_map *file);
uint8_t					get_magic_bit(uint32_t magic);
uint8_t					get_endianess(uint32_t magic);
uint8_t					get_fat(uint32_t magic);
uint32_t				swap_32(uint32_t value);
size_t					sizeof_header(t_header *header);

# endif
