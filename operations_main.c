#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "number.h"
#include "operations.h"

int main()
{

    Num *N1, *N2, *N;

    N1 = (Num *)malloc(sizeof(Num));
    N2 = (Num *)malloc(sizeof(Num));

    init(N1);
    init(N2);

    char no1[100], no2[100];

    printf("Enter 1st no : ");
    scanf("%s", &no1);
    printf("Enter 2nd no : ");
    scanf("%s", &no2);

    int i = 0;
    while (no1[i] != '\0')
    {
        if (no1[i] == '-')
        {
            N1->sign = 1;
            i++;
        }
        append(N1, no1[i]);
        i++;
    }

    i = 0;
    while (no2[i] != '\0')
    {
        if (no2[i] == '-')
        {
            N2->sign = 1;
            i++;
        }
        append(N2, no2[i]);
        i++;
    }
    int scale;
    printf("Enter scale:");
    scanf("%d", &scale);
    traverse(N1);
    traverse(N2);

    Num *sum, *diff, *mult, *div, *mod, *pow;
    sum = add(N1, N2);
    printf("addition:");
    traverse(sum);

    diff = sub(N1, N2);
    printf("subtraction:");
    traverse(diff);

    mult = multiply(N1, N2);
    printf("multiplication:");
    traverse(mult);

    div = divide(N1, N2, scale);
    printf("division:");
    traverse(div);

    pow = power(N1, N2);
    printf("power:");
    traverse(pow);
}
