/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 22:34:43 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/26 12:56:57 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

int			g_fat = 0;
int			g_archive = 0;
int			g_count = 0;
int			g_idx = 0;

int			main(int ac, char **av)
{
	t_map		info;
	int			i;

	i = 0;
	if (ac >= 2)
	{
		info.file = av + 1;
		info.mul_files = ac > 2;
		while (++i < ac)
			start_process_otool(av[i], info);
	}
	else
		send_error("usage: ./ft_otool [file...]");
	return (0);
}
