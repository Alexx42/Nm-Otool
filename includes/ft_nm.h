#ifndef FT_NM_H
# define FT_NM_H

#include <stdlib.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

#include "common.h"

char			*load_file(char *);
void			start_process(char *path);

# endif