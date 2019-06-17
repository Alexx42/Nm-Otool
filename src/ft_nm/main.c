/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 22:34:49 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/16 22:34:52 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		test(char *ptr)
{
	uint32_t				magic_number;
	struct mach_header_64	*header;
	struct load_command		*lc;

	header = malloc(sizeof(*header));
	magic_number = *(uint32_t*)ptr;
	ft_memcpy(header, ptr, sizeof(*header));
	printf("magic = %x\n", header->magic);
	printf("ncmds = %d\n", header->ncmds);
	printf("sizeof = %d\n", header->sizeofcmds);
	lc = malloc(sizeof(*lc));
	ft_memcpy(lc, (void *)ptr + sizeof(*header), sizeof(*lc));
	for (uint32_t i = 0; i < header->ncmds; i++)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			printf("THIS IS THE GOOD ONE\n");
			break ;
		}
		lc = (void *) lc + lc->cmdsize;
	}
}

int			main(int ac, char **av)
{
	struct stat buf;
	int			fd;
	char		*ptr;

	if (ac == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
		{
			ft_putstr_fd("Impossible to open the file\n", 2);
		}
		fstat(fd, &buf);
		ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		if (ptr == MAP_FAILED)
		{
			exit(1);
		}
		test(ptr);
	}
	else
	{
		ft_putstr("Invalid nb of arguments\n");
	}
	return (0);
}
