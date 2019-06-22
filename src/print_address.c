/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 23:59:24 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/21 19:33:11 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

void		print_address(size_t value, int length)
{
	if (length == 0)
		return ;
	print_address(value / 16, length - 1);
	write(1, &HEX[value % 16], 1);
}

void		print_file(char *file)
{
	write(1, "\n", 1);
	ft_putstr(file);
	ft_putendl(":");
}