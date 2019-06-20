/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:43:30 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 19:31:34 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		load_file(t_map *file, char *path)
{
	int			fd;
	struct stat buf;

	if ((fd = open(path, O_RDONLY)) < 0)
		send_error("Couldn't open the file");
	if ((fstat(fd, &buf)) == -1)
		send_error("Fstat failed");
	if (S_ISDIR(buf.st_mode))
		send_error("You're trying to open a directory");
	file->size = buf.st_size;
	if ((file->ptr = mmap(0, file->size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
		MAP_FAILED)
		send_error("Mmap failed");
}
