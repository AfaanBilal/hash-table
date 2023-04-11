/**
 * Hash Table
 *
 * @author Afaan Bilal
 * @link   https://afaan.dev
 * @link   https://github.com/AfaanBilal/hash-table
 */

#include <math.h>

#include "prime.h"

/*
 * Check if x is prime.
 *
 * Returns:
 *   1 - prime
 *   0 - not prime
 *   -1 - invalid input
 */
int is_prime(const int x)
{
    if (x < 2)
        return -1;

    if (x < 4)
        return 1;

    if ((x % 2) == 0)
        return 0;

    const int limit = floor(sqrt((double)x));
    for (int i = 3; i <= limit; i += 2)
        if ((x % i) == 0)
            return 0;

    return 1;
}

/*
 * Return x if x is prime or the next prime after x.
 */
int next_prime(int x)
{
    while (is_prime(x) != 1)
        x++;

    return x;
}
