/* MDH WCET BENCHMARK SUITE. File version $Id: fibcall.c,v 1.3 2005/11/11 10:30:19 ael01 Exp $ */

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
/*  FILE: fibcall.c                                                      */
/*  SOURCE : Public Domain Code                                          */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Summing the Fibonacci series.                                     */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

 /*
  * Changes: JG 2005/12/21: Inserted prototypes.
  *                         Indented program.
  */
#ifdef PRINT_RESULTS
#include <stdio.h>
#endif
int             fib(int n);

__attribute__((noinline))
int
fib(int n)
{
	int             i, Fnew, Fold, temp, ans;

	Fnew = 1;
	Fold = 0;
	for (i = 2;
	     i <= 30 && i <= n;	/* apsim_loop 1 0 */
	     i++) {
		temp = Fnew;
		Fnew = Fnew + Fold;
		Fold = temp;
	}
	ans = Fnew;
	return ans;
}

int
main()
{
	int             a;

	a = 30;
	int r = fib(a);
#ifdef PRINT_RESULTS
        printf("fib: r=%d\n", r);
#endif
        if(r != 832040) return 1;
	return 0;
}
