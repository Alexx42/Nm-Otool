/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:26:02 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/18 23:42:40 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

uint8_t		get_magic_bit(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

uint8_t		get_endianess(uint32_t magic)
{
	return (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM);
}

uint8_t		get_fat(uint32_t magic)
{
	return (magic == FAT_MAGIC || magic == FAT_CIGAM);
}