/* File: kalmpr.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MINNUM 2100000000
#define MAXNUM 2101000000
#define MAXK 5
#define COMPUTATIONS 20

int main() {
    int i, k, flag, tempcount, divisor, tempi, kalmostprimes, semiprimes, tspfactor1, tspfactor2,
        j, y, z, x, countk, tempx, divisor2;
    long curtime;
    semiprimes = 0;                                                                                                      /* Initialize count of semiprimes */
    kalmostprimes = 0;                                                                                              /* Initialize count of k-almost primes */
    printf("Checking numbers in [%d,%d]\n\n", MINNUM, MAXNUM);
    for (i = MINNUM ; i <= MAXNUM ; i++) {                                                            /* Repeat for every number between MINNUM and MAXNUM */                                          
        tempcount = 0;                                                                                          /* Initialize 'i''s count of prime factors */
        tempi = i;                                                                                /* Give the 'i''s value to a temporary variable('tempi') */
        tspfactor1 = 1;                                                    /* Temp semiprime factor1 is 1(will be used if 'i' is an interesting semiprime) */
        while ((2 * 2 <= tempi) && (tempi % 2 == 0)) {                        /* Count if and how many times 2 divides 'tempi' up to the square of 'tempi' */
            tempcount++;                                                               /* If 2 is divisor, the count of 'i''s prime factors increases by 1 */
            tempi = tempi/2;                                                                                                        /* Divide 'tempi' by 2 */
            tspfactor1 = 2;                                                                                                 /* Temp semiprime factor1 is 2 */
        }
        while ((3 * 3 <= tempi) && (tempi % 3 == 0)) {                        /* Count if and how many times 3 divides 'tempi' up to the square of 'tempi' */
            tempcount++;                                                               /* If 3 is divisor, the count of 'i''s prime factors increases by 1 */
            tempi = tempi/3;                                                                                                        /* Divide 'tempi' by 3 */
            tspfactor1 = 3;                                                                                                 /* Temp semiprime factor1 is 3 */
        }
        for (divisor = 5 ; divisor*divisor  <= tempi ; divisor+=6) { /* From 5 up to the square of 'tempi' check for the rest possible 'i''s prime factors */
            while (tempi % divisor == 0) {                                                          /* Count if and how many times 'divisor' divides tempi */
                tempcount++;                                                   /* If 'divisor' is divisor, the count of 'i''s prime factors increases by 1 */
                tempi = tempi/divisor;                                                                                      /* Divide 'tempi' by 'divisor' */
                tspfactor1 = divisor;                                                                               /* Temp semiprime factor1 is 'divisor' */
            }
            while (tempi % (divisor + 2 ) == 0) {                                                 /* Count if and how many times 'divisor'+2 divides tempi */
                tempcount++;                                                 /* If 'divisor'+2 is divisor, the count of 'i''s prime factors increases by 1 */
                tempi = tempi/(divisor + 2);                                                                              /* Divide 'tempi' by 'divisor'+2 */
                tspfactor1 = divisor + 2;                                                                         /* Temp semiprime factor1 is 'divisor'+2 */
            }
        }
        tspfactor2 = i / tspfactor1;                                                             /* Temp semiprime factor2 is 'i'/(Temp semiprime factor1) */
        if (tempi != 1 ) {                            /* If 'tempi' isn't 1 that means 'i' doesn't have any prime divisors up to his square, so it's prime */
            tempcount++;                                                             /* 'tempcount' becomes 1 (a prime number has 1 prime factor, himself) */
        }
        flag = 0;                                                                /* 'flag' will be used as a propositional variable(true or false, 1 or 0) */
        k = 2;                                                                                                           /* 'k' starts from 2 (2<=k<=MAXK) */
        while ( (k <= MAXK) && (flag == 0) ) {                                                             /* Stop if 'k' > MAXK or 'flag' becomes true(1) */
            if (tempcount == k) {                              /* If the number of 'i''s prime factors is equal to 'k' then 'i' is a k-almost prime number */
                kalmostprimes++;                                                                     /* The count of k-almost prime numbers increases by 1 */
                flag = 1;                                                  /* 'flag' becomes 1(true) in order to skip checking the rest times up to 'MAXK' */ 
                if (tempcount == 2) {                                                          /* If 'i' has 2 prime factors, then it's a semiprime number */
                    semiprimes++;                                                                         /* The count of semiprime numbers increases by 1 */
                /* If the first semi prime factor is smaller than the second semi prime factor up to 1% of the second,then 'i' is an interesting semiprime */
                    if (( tspfactor1 < tspfactor2 ) && ( tspfactor1 >= (tspfactor2 - (0.01 * tspfactor2 )))) {
                        printf("%d * %d = %d is an interesting semiprime\n", tspfactor1, tspfactor2, i );
                    }
                /* If the second semi prime factor is smaller than the first semi prime factor up to 1% of the first, then 'i' is an interesting semiprime */
                    else if (( tspfactor2 < tspfactor1 ) && ( tspfactor2 >= (tspfactor1 - (0.01 * tspfactor1 )))) {
                        printf("%d * %d = %d is an interesting semiprime\n", tspfactor2, tspfactor1, i );
                    }
                }
            }
            k++;                                                                                                                      /* Increase 'k' by 1 */
        }
    }
    printf("\nFound %d k-almost prime mumbers (2 <= k <= %d)\nFound %d semiprimes\n\n", kalmostprimes, MAXK, semiprimes);
    curtime = time(NULL);                                                                                                       /* Current time in seconds */
    srand((unsigned int) curtime);                                                                                     /* Seed for random number generator */
    printf("Current time is %ld\n\n", curtime);
    printf("Checking %d random numbers\n\n", COMPUTATIONS);
    for (j = 0 ; j < COMPUTATIONS ; j++) {                                                                              /* Repeat for 'COMPUTATIONS' times */
        y = rand();                                                                                                            /* Select 1st random number */
        z = rand();                                                                                                            /* Select 2nd random number */
        x = ((y % 32768) + 1)*((z % 32768) + 1) + 1;                                                 /* Create a new random number('x') using this formula */
        tempx = x;                                                                                    /* Give 'x''s value to a temporary variable('tempx') */
        countk = 0;                                                                                             /* Initialize 'x''s count of prime factors */    
        for (divisor2 = 2 ; divisor2 * divisor2 <= tempx ; divisor2++) {                              /* Search for prime divisors up to the square of 'x' */
            while (tempx % divisor2 == 0) {                                                      /* Count if and how many times 'divisor2' divides 'tempx' */
                countk++;                                                     /* If 'divisor2' is divisor, the count of 'x''s prime factors increases by 1 */
                tempx = tempx/divisor2;                                                                                    /* Divide 'tempx' by 'divisor2' */
            }
        }
        if (tempx != 1 ) {                                  /* If 'tempx' isn't 1 that means 'x' doesn't have any divisors up to his square, so it's prime */
            countk++;                                                                   /* 'countk' becomes 1 (a prime number has 1 prime factor, himself) */
        }
        printf("%d is a %d-almost prime number\n", x, countk);
    }
}