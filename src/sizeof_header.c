/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizeof_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:13:10 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/19 00:24:13 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

size_t		sizeof_header(t_header *header)
{
	if (header->fat_header)
		return (sizeof(struct fat_header *));
	else if (header->header_32)
		return (sizeof(struct mach_header *));
	else
		return (sizeof(struct mach_header_64 *));
}