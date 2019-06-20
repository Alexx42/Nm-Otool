/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 23:59:24 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/20 00:16:02 by ale-goff         ###   ########.fr       */
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