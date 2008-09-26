/* copper.c Debugging helper.
 * This file is a part of the Copper framework.
 * Copyright 2006-2008 Joshua Charles Campbell.

 * The Copper framework is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "copper.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>

#define MAXFLAGS 128

 /* debug levels */
static int dl[MAXFLAGS];

static int cu_builtin_vprintf(char const *f, va_list args) {
	return vfprintf(stderr, f, args);
}

static int (*cu_vprintf_handler)(const char *format, va_list args) = cu_builtin_vprintf;

int cu_printf(char const *f, ...) {
	va_list args; 
	int i;
	va_start(args, f);
	i = (*cu_vprintf_handler)(f, args);
	va_end (args); 
	return i;
}

static void cu_builtin_exit(int x) {
	exit(x);
}

static void (*cu_exit_handler)(int x) = cu_builtin_exit;

void cu_exit(int x) {
	(*cu_exit_handler)(x);
}

void cu_set_handlers(void (*provided_exit)(int x), int (*provided_vprintf)(const char *format, va_list args)) {
    if (provided_exit == NULL) {
        cu_exit_handler = cu_builtin_exit;
    } else {
        cu_exit_handler = provided_exit;
    }
    if (provided_vprintf == NULL) {
        cu_vprintf_handler = cu_builtin_vprintf;
    } else {
        cu_vprintf_handler = provided_vprintf;
    }
}

void cu_enabledebug(char* f) {
	int ifl; int fl;
	if (strcmp(f, "all") == 0) {
		for (ifl = 0; ifl < MAXFLAGS; ifl++) {
			dl[ifl] = 1;
		}
		D(("Every debug flag enabled."));
		return;
	} else {
		fl = strlen(f);
		for (ifl = 0; ifl < fl; ifl++) {
			dl[(int)f[ifl]] = 1;
		}
		dl[(int)'-'] = 1;
		D(("Debug flags enabled: %s", f));
		return;
	}
}

int cu_testdebug(char f) {
	return dl[(int)f];
}

char * cu_err() {
	return strerror(errno);
}
