/* copper.c Debugging helper.
 * Copyright 2006-2008 Joshua Charles Campbell

 * This program is free software; you can redistribute it and/or
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
#include "debug.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>

#define MAXFLAGS 128

static int dl[MAXFLAGS]; /* debug levels */

static int cu_builtin_printf(char const *f, ...) {
	va_list args; 
	int i;
	va_start(args, f);
	i = vfprintf(stderr, f, args); 
	va_end (args); 
	return i;
}

int (*cu_printf_handler)(const char *format, va_list ap) = cu_builtin_printf;

static void cu_builtin_exit(int x) {
	exit(x);
}

void (*cu_exit_handler)(int x) = cu_builtin_exit;

void cu_enabledebug(char* f) {
	int ifl; int fl;
	if (strcmp(f, "all") == 0) {
		for (ifl = 0; ifl < MAXFLAGS; ifl++) {
			dl[ifl] = 1;
		}
		D(("Every debug flag enabled.", f));
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

char * cu_derr() {
	return strerror(errno);
}
