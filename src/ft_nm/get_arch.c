/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:00:36 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/18 23:45:22 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		get_arch(char *ptr, t_arch *arch)
{
	arch->magic = *(int *)ptr;
	arch->endianness = get_endianess(arch->magic);
	arch->bit_arch = get_magic_bit(arch->magic);
	arch->is_fat = get_fat(arch->magic);
}