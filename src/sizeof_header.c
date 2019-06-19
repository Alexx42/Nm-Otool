/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizeof_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:13:10 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 10:43:46 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

size_t		sizeof_header(t_arch *arch)
{
	if (arch->is_fat)
		return (sizeof(struct fat_header));
	else if (!arch->bit_arch)
		return (sizeof(struct mach_header));
	else
		return (sizeof(struct mach_header_64));
}