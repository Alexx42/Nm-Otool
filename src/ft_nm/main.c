/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 22:34:49 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 14:20:47 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

int			main(int ac, char **av)
{
	t_map	info;
	int		i;

	i = 0;
	if (ac < 2)
	{
		send_error("usage: ./ft_nm [file]");
	}
	info.file = av + 1;
	info.mul_files = ac > 2;
	while (av[++i])
	{
		start_process_nm(av[i], info);
	}
	return (0);
}
