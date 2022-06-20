#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "getnext.h"

int main()
{

    token t[1000];

    Num *N;
    int j;
    char expr[2000];
    printf("Enter expression separated by spaces\n");
    gets(expr);

    getnext(expr, t);

        return 0;
}