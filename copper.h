/* debug.h Debugging helper header.
 * Copyright 2006-2007 Joshua Charles Campbell

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

/* debug shit */

/* error: always prints message and exits */
#define E(x) {dprint("!!! %s:%i ", __FILE__, __LINE__); dprint x; dprint("\n"); dexit(1);}

/* warning: always prints message */
#define W(x) {dprint("/!\\ %s:%i ", __FILE__, __LINE__); dprint x; dprint("\n");}

/* debug: only prints if enabled */
#ifdef ENABLE_DEBUG
#define DEBUG(l, x) {if(testdebug(l)) {dprint("--%c %s:%i ", l, __FILE__, __LINE__); dprint x; dprint("\n"); }}
#else /* ENABLE_DEBUG */
#define DEBUG(l, x)
#endif /* ENABLE_DEBUG */

/* error assertions: always executed, always checked, prints message */
#define EA(x, m) {if (!x) { DEBUG('@', ("Assertion failed: %s", #x)); dprint("!!? %s:%i ", __FILE__, __LINE__); dprint m; dprint("\n"); dexit(1);} else { DEBUG('@', ("Assertion passed: %s", #x)) } }

/* assertions: always executed, always checked */
#define A(x) EA(x, ("Assertion failed."))

/* system assertions: always executed, always checked, prints errno */
#define ASYS(x) EA(x, ("%s", derr()))

/* sanity check: only executed if enabled */
#ifdef ENABLE_SANITY
#define ES(x, m) {if (!x) { DEBUG('$', ("Sanity check failed: %s", #x)); dprint("!!$ %s:%i ", __FILE__, __LINE__); dprint m; dprint("\n"); dexit(1);} else { DEBUG('$', ("Sanity check passed: %s", #x)) } }
#else /* ENABLE_SANITY */
#define ES(x, m)
#endif /* ENABLE_SANITY */
#define S(x) ES(x, ("Sanity check failed."))

/* sanity assertion: always executed, only checked if enabled */
#ifdef ENABLE_SANITY
#define SA(x) S(x)
#else /* ENABLE_SANITY */
#define SA(x) (x)
#endif /* ENABLE_SANITY */

/* shortcuts */
#define D(x) DEBUG('-', x)
#define DE(x) DEBUG('E', x) /* */
#define De(x) DEBUG('e', x)
#define DI(x) DEBUG('I', x) /* input */
#define Di(x) DEBUG('i', x)
#define DM(x) DEBUG('M', x) /* main */
#define Dm(x) DEBUG('m', x)
#define DO(x) DEBUG('O', x) /* output */
#define Do(x) DEBUG('o', x)
#define DP(x) DEBUG('P', x) /* parser */
#define Dp(x) DEBUG('p', x)
#define DT(x) DEBUG('T', x) /* types */
#define Dt(x) DEBUG('t', x)
#define DU(x) DEBUG('U', x) /* util */
#define Du(x) DEBUG('u', x)
#define DW(x) DEBUG('W', x) /* word */
#define Dw(x) DEBUG('w', x)

/* function prototypes */
extern int dprint(char const *f, ...);
extern void dexit(int x);
extern void enabledebug(char* f);
extern int testdebug(char f);
extern char * derr();

/* end debug shit */

#endif /* _DEBUG_H_ */
