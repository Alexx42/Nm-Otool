/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 21:19:21 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 10:28:24 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static struct mach_header_64	*get_header_64(char *ptr)
{
	struct mach_header_64		*header;

	header = (struct mach_header_64 *)ptr;
	return (header);
}

static struct mach_header		*get_header_32(char *ptr)
{
	struct mach_header			*header;

	header = (struct mach_header *)ptr;
	return (header);
}

static struct fat_header		*get_fat_header(char *ptr)
{
	struct fat_header			*header;

	header = (struct fat_header *)ptr;
	return (header);
}

int								get_header(t_map *file,
								t_arch *arch, t_header *header)
{
	if (arch->magic && !arch->is_fat)
	{
		if ((header->header_64 = get_header_64(file->ptr)) == NULL)
			return (1);
		header->header_32 = NULL;
		header->fat_header = NULL;
	}
	else if (!arch->is_fat)
	{
		if ((header->header_32 = get_header_32(file->ptr)) == NULL)
			return (1);
		header->header_64 = NULL;
		header->fat_header = NULL;
	}
	else
	{
		if ((header->fat_header = get_fat_header(file->ptr)) == NULL)
			return (1);
		header->header_64 = NULL;
		header->header_32 = NULL;
	}
	return (0);
}
