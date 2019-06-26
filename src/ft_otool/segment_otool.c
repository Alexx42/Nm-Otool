/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_otool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:15:06 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 21:55:08 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

static void		print_otool_32(char *ptr, uint64_t size,
				uint64_t addr, t_arch *arch)
{
	int			i;

	i = 0;
	while (i < (int)size)
	{
		if (i % 16 == 0)
		{
			print_address(addr + i, 8);
			ft_putchar('\t');
		}
		print_address(ptr[i], 2);
		if (!arch->is_big_endian)
			ft_putchar(' ');
		if (arch->is_big_endian && i % 4 == 3)
			ft_putchar(' ');
		if (i % 16 == 15 || i + 1 >= (int)size)
			ft_putchar('\n');
		i++;
	}
}

static void		print_otool_64(char *ptr, uint64_t size,
				uint64_t addr, t_arch *arch)
{
	int			i;

	i = 0;
	while (i < (int)size)
	{
		if (i % 16 == 0)
		{
			print_address(addr + i, 16);
			ft_putchar('\t');
		}
		print_address(ptr[i], 2);
		if (!arch->is_big_endian)
			ft_putchar(' ');
		if (arch->is_big_endian && i % 4 == 3)
			ft_putchar(' ');
		if (i % 16 == 15 || i + 1 >= (int)size)
			ft_putchar('\n');
		i++;
	}
}

void			parse_segment_32(struct segment_command *segment,
				t_arch *arch, t_map *file)
{
	uint32_t			i;
	struct section		*section;
	uint32_t			val;

	i = -1;
	val = should_swap_32(arch, segment->nsects);
	section = (struct section *)((void *)segment + sizeof(*segment));
	while (++i < val)
	{
		error_out_of_memory(file, section + i);
		if (IS_TYPE((section + i)->sectname, SECT_TEXT, (section + i)->segname,
		SEG_TEXT))
		{
			ft_putendl("Contents of (__TEXT,__text) section");
			print_otool_32(file->ptr +
			should_swap_32(arch, (section + i)->offset),
			should_swap_32(arch, (section + i)->size),
			should_swap_32(arch, (section + i)->addr), arch);
		}
	}
}

void			parse_segment_64(struct segment_command_64 *segment,
				t_arch *arch, t_map *file)
{
	uint32_t			i;
	struct section_64	*section;
	uint32_t			val;

	i = -1;
	val = should_swap_64(arch, segment->nsects);
	section = (struct section_64 *)((void *)segment + sizeof(*segment));
	while (++i < val)
	{
		error_out_of_memory(file, section + i);
		if (IS_TYPE((section + i)->sectname, SECT_TEXT, (section + i)->segname,
			SEG_TEXT))
		{
			ft_putendl("Contents of (__TEXT,__text) section");
			print_otool_64(file->ptr +
			should_swap_64(arch, (section + i)->offset),
			should_swap_64(arch, (section + i)->size),
			should_swap_64(arch, (section + i)->addr), arch);
		}
	}
}
