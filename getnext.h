
#include "number.h"
typedef struct token
{
    int type;
    struct data

    {
        Num *num;
        char op;
    } data;
} token;

token t[1000];
Num *N;
void init(Num *N);
void append(Num *N, char ch);
void traverse(Num *N);
int getnext(char expr[], token t[]);
