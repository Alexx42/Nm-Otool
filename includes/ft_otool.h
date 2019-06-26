/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:20:56 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 20:40:27 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H
# include <common.h>

void		start_process_otool(char *filename, t_map *file);
void		print_file_otool(char *file);
void		launch_process_otool(t_map *file, t_arch *arch,
			t_header *header);

#endif
