#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include "infix.h"

// t[j].type=100, for integer token
// t[j].type=200, for character operator token
// t[j].type=300, for space
// t[j].type=400, for possible errors
// t[j].type=500, for end of expression
// flag==-1 indicates error

void init1(stack1 *s)
{
    s->top1 = -1;
    s->size1 = 1000;
}

void init2(stack2 *s)
{
    s->top2 = -1;
    s->size2 = 1000;
}
int isempty1(stack1 *s)
{
    if (s->top1 == -1)
        return 1;
    else
        return 0;
}

int isfull1(stack1 *s)
{
    if (s->top1 == s->size1 - 1)
        return 1;
    else
        return 0;
}

int isempty2(stack2 *s)
{
    if (s->top2 == -1)
        return 1;
    else
        return 0;
}

int isfull2(stack2 *s)
{
    if (s->top2 == s->size2 - 1)
        return 1;
    else
        return 0;
}

void push1(stack1 *s, Num *N)
{
    if (isfull1(s))
    {
        printf("Stack1 is full\n");
    }
    else
    {
        s->top1++;
        s->i[s->top1] = N;
    }
}

void push2(stack2 *s, char val)
{
    if (isfull2(s))
    {
        printf("Stack2 is full\n");
    }
    else
    {
        s->top2++;
        s->op[s->top2] = val;
    }
}

Num *pop1(stack1 *s)
{
    Num *x;
    if (isempty1(s))
    {
        printf("Stack1 is empty\n");
    }
    else
    {
        x = s->i[s->top1];
        s->top1--;
    }

    return x;
}

char pop2(stack2 *s)
{
    char x;
    if (isempty2(s))
    {
        printf("Stack2 is empty\n");
    }
    else
    {
        x = s->op[s->top2];
        s->top2--;
    }

    return x;
}

int precedance(char op)
{

    switch (op)
    {
    case '+':
        return 10;
    case '-':
        return 10;
    case '*':
        return 20;
    case '/':
        return 20;
    case '^':
        return 30;
    case '(':
        return 40;
    }
}

Num *applyOp(Num *N1, Num *N2, Num *res, char op)
{
    switch (op)
    {
    case '+':
        res = add(N1, N2);
        break;
    case '-':
        res = sub(N1, N2);
        break;
    case '*':
        res = multiply(N1, N2);
        break;
    case '/':
        res = divide(N1, N2, 4);
        break;

    case '^':
        res = power(N1, N2);
        break;
    case '%':
        res = modula(N1, N2);
    default:
        break;
    }
    return res;
}

Num *evaluate(token t[], stack1 s1, stack2 s2)
{
    Num *opr2, *opr1;
    opr2 = (Num *)malloc(sizeof(Num));
    init(opr2);
    opr1 = (Num *)malloc(sizeof(Num));
    init(opr1);
    Num *c;
    c = (Num *)malloc(sizeof(Num));
    init(c);

    int k, j;
    for (j = 0; t[j].type != 500; j++)
    {

        if (t[j].type == 100)
        {

            push1(&s1, t[j].data.num);
        }
        else if (t[j].type == 300)
        {
            continue;
        }
        else if (t[j].data.op == '(')
        {
            push2(&s2, t[j].data.op);
        }
        else if (t[j].data.op == ')')
        {

            while (!isempty2(&s2) && s2.op[s2.top2] != '(')
            {
                opr2 = pop1(&s1);
                opr1 = pop1(&s1);
                char op = pop2(&s2);
                c = applyOp(opr1, opr2, c, op);
                push1(&s1, c);
            }
            if (!isempty2(&s2))
                pop2(&s2);
        }

        else if (t[j].type == 200 && t[j].data.op != '(' && t[j].data.op != ')')
        {
            int p1 = precedance(s2.op[s2.top2]);
            int p2 = precedance(t[j].data.op);

            while (!isempty2(&s2) && (p1 >= p2) && !isempty1(&s1))
            {

                char op = pop2(&s2);
                if (op == '(')
                {
                    push2(&s2, op);
                    break;
                }
                opr2 = pop1(&s1);
                opr1 = pop1(&s1);

                c = applyOp(opr1, opr2, c, op);
                push1(&s1, c);
            }
            push2(&s2, t[j].data.op);
        }
    }

    while (!isempty2(&s2))
    {

        opr2 = pop1(&s1);
        opr1 = pop1(&s1);
        char op = pop2(&s2);
        c = applyOp(opr1, opr2, c, op);
        push1(&s1, c);
    }
    Num *ans1;
    ans1 = (Num *)malloc(sizeof(Num));
    init(ans1);
    ans1 = s1.i[s1.top1];
    return ans1;
}
