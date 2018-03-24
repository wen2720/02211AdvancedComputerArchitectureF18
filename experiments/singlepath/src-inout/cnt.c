/* MDH WCET BENCHMARK SUITE. File version $Id: cnt.c,v 1.4 2005/11/11 10:25:48 ael01 Exp $ */

/* cnt.c */

/* Changes:
 * JG 2005/12/12: Indented program.
 */

/* #include <sys/types.h */
/* #include <sys/times.h> */

/* #define WORSTCASE 1 */
/* #define MAXSIZE 100 Changed JG/Ebbe */
#define MAXSIZE 10

/* Typedefs */
typedef int     matrix[MAXSIZE][MAXSIZE];

/* Forwards declarations */
int             main(void);
int             Test(matrix);
int             Initialize(matrix);
int             InitSeed(int);
void            Sum(matrix);
int             RandomInteger(void);

/* Globals */
int             Seed;
matrix          Array;
int             Postotal, Negtotal, Poscnt, Negcnt;

/* The main function */
__attribute__((noinline))
int 
main_test(int in_seed)
{
	InitSeed(in_seed);
	/* printf("\n   *** MATRIX SUM AND COUNT BENCHMARK TEST ***\n\n"); */
	/* printf("RESULTS OF THE TEST:\n"); */
	Test(Array);
	return 1;
}


__attribute__((singlepath,noinline))
int 
Test(matrix Array)
{
	Initialize(Array);
	Sum(Array);
	return 0;
}


/* Intializes the given array with random integers. */
int 
Initialize(matrix Array)
{
	register int    OuterIndex, InnerIndex;

	for (OuterIndex = 0; OuterIndex < MAXSIZE; OuterIndex++)	/* 100 + 1 */
		for (InnerIndex = 0; InnerIndex < MAXSIZE; InnerIndex++)	/* 100 + 1 */
			Array[OuterIndex][InnerIndex] = RandomInteger();

	return 0;
}


/* Initializes the seed used in the random number generator. */
int 
InitSeed(int in_seed)
{
	Seed = in_seed % 8095;
	return 0;
}

void 
Sum(matrix Array)
{
	register int    Outer, Inner;

	int             Ptotal = 0;	/* changed these to locals in order
					 * to drive worst case */
	int             Ntotal = 0;
	int             Pcnt = 0;
	int             Ncnt = 0;

	for (Outer = 0; Outer < MAXSIZE; Outer++)	/* Maxsize = 100 */
		for (Inner = 0; Inner < MAXSIZE; Inner++)
#ifdef WORSTCASE
			if (Array[Outer][Inner] >= 0) {
#else
			if (Array[Outer][Inner] < 0) {
#endif
				Ptotal += Array[Outer][Inner];
				Pcnt++;
			} else {
				Ntotal += Array[Outer][Inner];
				Ncnt++;
			}

	Postotal = Ptotal;
	Poscnt = Pcnt;
	Negtotal = Ntotal;
	Negcnt = Ncnt;
}


/*
This function returns in milliseconds the amount of compiler time
 int ttime()
 {
   struct tms buffer;
 int utime;

 times(&buffer);
 utime = (buffer.tms_utime / 60.0) * 1000.0;
 return (utime);
 }
*/

/* Generates random integers between -8095 and 8095 */
int 
RandomInteger(void)
{
	Seed = (((Seed * 133) + 81) % 16190);
	return Seed - 8095;
}
