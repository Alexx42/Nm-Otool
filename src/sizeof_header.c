/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizeof_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:13:10 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/24 19:29:14 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

size_t		sizeof_header(t_arch *arch)
{
	if (arch->is_fat)
		return (sizeof(struct fat_header));
	else if (arch->is_archive)
		return (sizeof(struct ar_hdr));
	else if (arch->is_64)
		return (sizeof(struct mach_header_64));
	else if (!arch->is_64)
		return (sizeof(struct mach_header));
	return (0);
}
