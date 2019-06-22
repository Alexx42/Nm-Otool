/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 22:10:58 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/21 21:44:33 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int		g_count = 0;

t_info_sec		*get_section(void)
{
	static t_info_sec	seg = {0, 0, 0};

	return (&seg);
}

void			init_section(void)
{
	get_section()->bss = 0;
	get_section()->data = 0;
	get_section()->text = 0;
}

void			parse_segment(struct segment_command_64 *segment, t_arch *arch)
{
	uint32_t			i;
	struct section_64	*section;

	i = 0;
	if (arch->is_big_endian)
		swap_segment_command_64(segment, 0);
	section = (struct section_64 *)((void *)segment + sizeof(*segment));
	if (arch->is_big_endian)
		swap_section_64(section, 0, 0);
	while (i < segment->nsects)
	{
		if (IS_TYPE((section + i)->sectname, SECT_TEXT, (section + i)->segname,
																	SEG_TEXT))
			get_section()->text = g_count + 1;
		if (IS_TYPE((section + i)->sectname, SECT_DATA, (section + i)->segname,
																	SEG_DATA))
			get_section()->data = g_count + 1;
		if (IS_TYPE((section + i)->sectname, SECT_BSS, (section + i)->segname,
																	SEG_DATA))
			get_section()->bss = g_count + 1;
		g_count++;
		i++;
	}
}
