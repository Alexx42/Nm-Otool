/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_archive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 19:49:29 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/26 00:16:15 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

extern int	g_count;
extern int	g_archive;
extern int	g_idx;

static void		print_filename(char *src, char *file)
{
	write(1, "\n", 1);
	ft_putstr(src);
	write(1, "(", 1);
	ft_putstr(file);
	write(1, ")", 1);
	write(1, ":\n", 2);
}

static void		file_archive(t_arch *arch, t_header *header,
				t_map *file)
{
	size_t		len;
	char		*tmp;
	char		*str;

	str = file->ptr + sizeof(struct ar_hdr);
	print_filename(file->file[g_idx], str);
	len = ft_strlen(str);
	while (!str[len++])
		;
	tmp = file->ptr;
	file->ptr += sizeof(struct ar_hdr) + len - 1;
	launch_process(file, arch, header);
	file->ptr = tmp;
}

void			process_archive(t_map *file,
				t_arch *arch, t_header *header)
{
	struct ar_hdr	*ar;

	ar = header->archive_header;
	g_archive = 1;
	file->ptr = file->ptr + SARMAG + ft_atoi(ar->ar_size) + sizeof(*ar);
	while (file->ptr)
	{
		ar = (struct ar_hdr *)file->ptr;
		if (ft_atoi(ar->ar_size) <= 0)
			return ;
		if ((void *)file->ptr + (ft_atoi(ar->ar_size) + sizeof(*ar)) >
		file->max_size)
			return ;
		file_archive(arch, header, file);
		file->ptr = file->ptr + ft_atoi(ar->ar_size) + sizeof(*ar);
	}
	g_archive = 0;
}
