/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:45:03 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 23:35:34 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		send_error(char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

void		error_munmap(char *message, t_map *file)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	munmap(file->ptr, file->size);
	exit(1);
}

void		error_out_of_memory(t_map *file, void *ptr)
{
	if (ptr > file->max_size)
	{
		error_munmap("The file is malformed or has been truncated", file);
	}
}
