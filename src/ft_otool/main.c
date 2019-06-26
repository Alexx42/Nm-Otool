/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 22:34:43 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/25 17:42:52 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

int			g_fat = 0;
int			g_archive = 0;
int			g_count = 0;
int			g_idx = 0;

int			main(int ac, char **av)
{
	t_map		file;
	int			i;

	i = 1;
	if (ac >= 2)
	{
		file.file = av + 1;
		while (i < ac)
		{
			start_process_otool(av[i++], &file);
		}
	}
	else
	{
		send_error("usage: ./ft_otool [file...]");
	}
	return (0);
}
