/* MDH WCET BENCHMARK SUITE. File version $Id: insertsort.c,v 1.3 2005/11/11 10:30:41 ael01 Exp $ */

/*************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                           sslim@archi.snu.ac.kr       */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: insertsort.c                                                   */
/*  SOURCE : Public Domain Code                                          */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Insertion sort for 10 integer numbers.                            */
/*     The integer array a[] is initialized in main function.            */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

/* Changes:
 * JG 2005/12/12: Indented program.
 */
#ifdef PRINT_RESULTS
#include <stdio.h>
#endif

int             cnt1, cnt2;

unsigned int    a[11];

__attribute__((noinline))
int
main()
{
	int             i, j, temp;

	a[0] = 0;		/* assume all data is positive */
	a[1] = 11;
	a[2] = 10;
	a[3] = 9;
	a[4] = 8;
	a[5] = 7;
	a[6] = 6;
	a[7] = 5;
	a[8] = 4;
	a[9] = 3;
	a[10] = 2;
	i = 2;
	while (i <= 10) {
		cnt1++;
		j = i;
		cnt2 = 0;
		while (a[j] < a[j - 1]) {
			cnt2++;
			temp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = temp;
			j--;
		}
#ifdef PRINT_RESULTS
		printf("insertsort: Inner Loop Counts: %d\n", cnt2);
#endif
		i++;
	}
#ifdef PRINT_RESULTS
	printf("insertsort: Outer Loop : %d ,  Inner Loop : %d\n", cnt1, cnt2);
        printf("insertsort: a[5]=%d\n",a[5]);
#endif
        if(cnt1 != 9 || cnt2 != 9) return 1;
        if(a[5] != 6) return 1;
	return 0;
}
