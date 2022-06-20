#include <stdio.h>
#include <stdlib.h>
#include "number.h"
int main()
{
    Num *N1, *N2, *s;
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
    printf("First number : ");
    traverse(N1);

    printf("Second number : ");
    traverse(N2);

    return 0;
}