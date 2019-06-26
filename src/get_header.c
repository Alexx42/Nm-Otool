/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 21:19:21 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/22 16:09:07 by ale-goff         ###   ########.fr       */
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

static struct ar_hdr			*get_archive_header(char *ptr)
{
	struct ar_hdr				*header;

	header = (struct ar_hdr *)((void *)ptr + SARMAG);
	return (header);
}

int								get_header(t_map *file,
								t_arch *arch, t_header *header)
{
	if (arch->is_64 && !arch->is_fat && !arch->is_archive)
	{
		if ((header->header_64 = get_header_64(file->ptr)) == NULL)
			return (1);
	}
	else if (!arch->is_fat && !arch->is_archive)
	{
		if ((header->header_32 = get_header_32(file->ptr)) == NULL)
			return (1);
	}
	else if (arch->is_archive)
	{
		if ((header->archive_header = get_archive_header(file->ptr)) == NULL)
			return (1);
	}
	else if (arch->is_fat)
	{
		if ((header->fat_header = get_fat_header(file->ptr)) == NULL)
			return (1);
	}
	return (0);
}
