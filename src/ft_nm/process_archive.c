/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_archive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 19:49:29 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 14:12:37 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

extern int	g_count;
int			g_archive = 0;

static void		print_filename(char *src, char *file)
{
	write(1, "\n", 1);
	ft_putstr(src);
	write(1, "(", 1);
	ft_putstr(file);
	write(1, ")", 1);
	write(1, ":\n", 2);
}

void			process_archive(t_map *file,
				t_arch *arch, t_header *header)
{
	struct ar_hdr	*ar;
	char			*str;
	char			*tmp;
	size_t			len;

	ar = header->archive_header;
	g_archive = 1;
	file->ptr = (char *)file->ptr + SARMAG + ft_atoi(ar->ar_size) + sizeof(*ar);
	while (file->ptr)
	{
		ar = (struct ar_hdr *)file->ptr;
		if (ft_atoi(ar->ar_size) <= 0)
			return ;
		str = file->ptr + sizeof(*ar);
		print_filename(file->file[0], str);
		len = ft_strlen(str);
		while (!str[len++])
			;
		tmp = file->ptr;
		file->ptr += sizeof(*ar) + len - 1;
		launch_process(file, arch, header);
		file->ptr = tmp;
		file->ptr = file->ptr + ft_atoi(ar->ar_size) + sizeof(*ar);
	}
	g_archive = 0;
}
