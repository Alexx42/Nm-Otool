/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:14:10 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/24 19:30:40 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

uint32_t		swap_32(uint32_t value)
{
	return (((value & 0x000000FF) << 24) |
	((value & 0x0000FF00) << 8) |
	((value & 0x00FF0000) >> 8) |
	((value & 0xFF000000) >> 24));
}

uint64_t		swap_64(uint64_t value)
{
	value = ((value << 8) & 0xFF00FF00FF00FF00ULL)
	| ((value >> 8) & 0x00FF00FF00FF00FFULL);
	value = ((value << 16) & 0xFFFF0000FFFF0000ULL)
	| ((value >> 16) & 0x0000FFFF0000FFFFULL);
	return (value << 32) | (value >> 32);
}

uint64_t		should_swap_64(t_arch *arch, uint64_t value)
{
	if (arch->is_big_endian)
		value = swap_64(value);
	return (value);
}

uint32_t		should_swap_32(t_arch *arch, uint32_t value)
{
	if (arch->is_big_endian)
		value = swap_32(value);
	return (value);
}
