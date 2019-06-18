/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:43:30 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/17 18:43:35 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

char		*load_file(char *path)
{
	char		*ptr;
	int			fd;
	struct stat buf;

	if ((fd = open(path, O_RDONLY)) < 0)
		send_error("Couldn't open the file");
	if ((fstat(fd, &buf)) == -1)
		send_error("Fstat failed");
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		send_error("Mmap failed");
	return (ptr);
}
