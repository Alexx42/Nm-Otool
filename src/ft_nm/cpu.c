/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 12:57:19 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/24 19:26:14 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static t_cpu_type_names		g_cpu_type_names[] = {
	{ CPU_TYPE_I386, "i386"},
	{ CPU_TYPE_X86_64, "x86_64"},
	{ CPU_TYPE_ARM, "arm"},
	{ CPU_TYPE_ARM64, "arm64"},
	{ CPU_TYPE_POWERPC, "ppc"},
	{ CPU_TYPE_POWERPC64, "ppc64"}
};

const char			*cpu_type_name(cpu_type_t cpu_type)
{
	int			i;
	int			size;

	i = -1;
	size = sizeof(g_cpu_type_names) / sizeof(t_cpu_type_names);
	while (++i < size)
	{
		if (cpu_type == g_cpu_type_names[i].cputype)
			return (g_cpu_type_names[i].cpu_name);
	}
	return ("unknown");
}

int					cpu_host(const char *cpu)
{
	if (!ft_strcmp(cpu, "i386") || !ft_strcmp(cpu, "x86_64"))
		return (1);
	return (0);
}

void				print_architecture(const char *cpu, char *filename)
{
	write(1, "\n", 1);
	ft_putstr(filename);
	ft_putstr(" (for architecture ");
	ft_putstr(cpu);
	ft_putendl("):");
}
