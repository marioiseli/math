/*
  * Written on a boring evening, on my journey to learn a bit of mathematics
  * Wanted to get an impression of how big numbers really can be
  *
  * (C) 2021 - Mario Iseli <mario@marioiseli.com>
  * 
*/

#include <gmp.h>
#include <stdio.h>
#include <time.h>

// increment per iteration (currently 10^18 aka quintillion)
#define INCREMENT 1000000000000000000

// after how many cycles (adding INCREMENT to iterator) to report status, 10^9
#define REPORT 1000000000

int main(int argc, char* argv[])
{
	mpz_t ten;
	mpz_init(ten);
	mpz_set_str(ten, "10", 10);

	mpz_t googol;
	mpz_init(googol);
	mpz_pow_ui(googol, ten, 100);

	// the "real" iterator - the number to increase by INCREMENT every time
	mpz_t i;
	mpz_init(i);

	mpz_t d1, d2, d3;
	mpz_init(d1);
	mpz_init(d2);
	mpz_init(d3);

	// j is the iterator for runtime statistics
	unsigned long j = 0;

	// td = timedifference, t1 = start of program, t2 = current time
	unsigned long td = 0;
	time_t t1 = time(NULL);
	time_t t2;

	//printf("ULONG_MAX: %lu\n", ULONG_MAX);

	while(mpz_cmp(i, googol) < 0)
	{
		j++;

		// i+= INCREMENT basically
		mpz_add_ui(i, i, INCREMENT);		

		// every 10^9 iterations, print status of i
		if(j == REPORT)
		{
			// Reset counter
			j = 0;
			t2 = time(NULL);
			td = (t2-t1);
			if(td > 0)
			{
				printf("+++\n");
				printf("Current time:\t\t%s", asctime(localtime(&t2)));
				printf("Running for:\t\t%lu seconds\n", td);
				// How much left to reach Googol
				mpz_sub(d1, googol, i);
				// Growth rate per second
				mpz_cdiv_q_ui(d2, i, td);
				//  How many seconds to reach Googol
				mpz_cdiv_q(d3, d1, d2);
				// Convert to years
				mpz_cdiv_q_ui(d3, d3, (86400*365));
				// Convert to earth ages, 1 ey eq. 4.54 billion years, source: https://en.wikipedia.org/wiki/Age_of_Earth
				mpz_cdiv_q_ui(d3, d3, 4540000000);
				gmp_printf("Running for another approx. %Zd earth ages\n", d3);
				gmp_printf("i: %Zd\n", i);
				printf("+++\n");
			}
		}
	}
}
