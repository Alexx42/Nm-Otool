/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:45:03 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/24 19:26:04 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		send_error(char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar('\n');
	exit(1);
}

void		error_munmap(char *message, t_map *file)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar('\n');
	munmap(file->ptr, file->size);
	exit(1);
}

void		error_out_of_memory(t_map *file, void *ptr)
{
	if (ptr > file->max_size)
	{
		error_munmap("Invalid object file, the object file has been truncated \
		or is invalid.", file);
	}
}
