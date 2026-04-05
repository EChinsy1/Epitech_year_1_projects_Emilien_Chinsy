/*
** EPITECH PROJECT, 2025
** my_find_prime_sup
** File description:
** task 7 day 5, I have to find the smallest,
**  prime number from the target
*/

#include <math.h>
#include "my.h"

int my_find_prime_sup(double nb)
{
    double sqrted = sqrt(nb);
    int result = ceil(sqrted);

    return (pow(result, 2));
}
