#include "getnext.h"
#include "operations.h"

typedef struct stack1
{
    int top1;
    int size1;
    Num *i[1000];

} stack1;
stack1 s1;

typedef struct stack2
{
    int top2;
    int size2;
    char op[1000];

} stack2;
stack2 s2;

Num *c;
void init1(stack1 *s);
void init2(stack2 *s);

void push1(stack1 *s, Num *N);

void push2(stack2 *s, char val);

Num *pop1(stack1 *s);
char pop2(stack2 *s);
void init1(stack1 *s);
void init2(stack2 *s);
int isempty1(stack1 *s);
int isempty2(stack2 *s);
int precedance(char op);
Num *applyOp(Num *N1, Num *N2, Num *res, char op);

Num *evaluate(token t[], stack1 s1, stack2 s2);

Num *add(Num *N1, Num *N2);
Num *sub(Num *N1, Num *N2);
void adjust_Number(Num *N1, Num *N2);
Num *multiply(Num *N1, Num *N2);
Num *mul_fun(Num *N1, char data, int k);
Num *divide(Num *N1, Num *N2, int scale);
Num *modula(Num *N1, Num *N2);
Num *square(Num *N);
