/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:57:35 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 17:19:55 by ale-goff         ###   ########.fr       */
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
# include <common.h>

typedef struct s_map			t_map;
typedef struct s_arch			t_arch;
typedef struct s_header			t_header;
typedef struct s_cpu_type_names t_cpu_type_names;
typedef struct s_info_sec		t_info_sec;
typedef struct s_symbol			t_symbol;

void						start_process_nm(char *path, t_map file);
void						launch_process(t_map *file, t_arch *arch,
							t_header *header);

#endif
