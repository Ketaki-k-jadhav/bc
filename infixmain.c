#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include "infix.h"

int main()
{
    stack1 s1;
    stack2 s2;
    Num *c;

    char expr[2000];
    printf("Enter expression separated by spaces\n");
    gets(expr);
    int flag = getnext(expr, t);
    init1(&s1);
    init2(&s2);

    if (flag != -1)
    {
        Num *ans;
        ans = (Num *)malloc(sizeof(Num));
        init(ans);
        ans = evaluate(t, s1, s2);
        printf("Result of above expression:\n");
        traverse(ans);
    }
    else
    {
        printf("Invalid expression...cannot be evaluated.\n");
    }

    return 0;
}