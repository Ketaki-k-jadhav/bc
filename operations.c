#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "number.h"
#include "operations.h"

/*
 * Takes argument as Num pointer of 2 Numbers
 * Adds 2 numbers and returns Nadd Number
 */

Num *add(Num *N1, Num *N2)
{
    if (!N1 || !N2)
        return NULL;

    Num *Nadd = (Num *)malloc(sizeof(Num));
    init(Nadd);
    if (N1->sign == N2->sign) // a + b or -a + (-b)
        Nadd->sign = N1->sign;
    else if (N1->sign == 0 && N2->sign == 1)
    { // a + (-b) i.e, equivalent to  a - b
        N2->sign = 0;
        Nadd = sub(N1, N2);
        N2->sign = 1;
        return Nadd;
    }
    else
    { // -a + b i.e, equivalent to b - a
        N2->sign = 1;
        Nadd = sub(N1, N2);
        N2->sign = 0;
        return Nadd;
    }

    adjust_Number(N1, N2);
    node *p = N1->tail, *q = N2->tail;

    int carry = 0;
    char c;

    while (p && q)
    {
        c = p->data + q->data - 48 + carry;
        if (c > 57)
        {
            c = c - 10;
            carry = 1;
        }
        else
            carry = 0;
        push(Nadd, c);
        p = p->prev;
        q = q->prev;
    }
    if (carry == 1)
        push(Nadd, '1');

    if (N1->decimal > 0)
    {
        Nadd->decimal = N1->decimal;
        Nadd->integer = Nadd->integer - Nadd->decimal;
    }

    return Nadd;
}

/* Takes arguments as Num pointer of 2 Numbers
 * Subtract 2 NUmbers
 * Returns Nsub
 */
Num *sub(Num *N1, Num *N2)
{
    if (!N1 || !N2)
        return NULL;

    int flag = 0;
    if (compare(N1, N2) == 0 && N1->sign == N2->sign)
    { // If 1st Number is smaller than 2nd Number
        swap_Number(N1, N2);
        flag = 1; // Set flag to 1
    }

    Num *Nsub = (Num *)malloc(sizeof(Num));
    init(Nsub);
    if (N1->sign == N2->sign)
    { // a - b or -a - ( -b ) i.e, b - a for this sign will change
        Nsub->sign = N1->sign;
    }
    else if (N1->sign == 0 && N2->sign == 1)
    { // a - ( -b ) i.e, a + b
        N2->sign = 0;
        Nsub = add(N1, N2);
        N2->sign = 1;
        return Nsub;
    }
    else
    { // -a - b i.e, -a + ( -b )
        N2->sign = 1;
        Nsub = add(N1, N2);
        N2->sign = 0;
        return Nsub;
    }

    adjust_Number(N1, N2);
    node *p = N1->tail, *q = N2->tail;

    int borrow = 0;
    char c;

    while (p && q)
    {
        c = p->data - q->data + 48 - borrow;
        if (c < 48)
        {
            c = c + 10;
            borrow = 1;
        }
        else
            borrow = 0;
        push(Nsub, c);
        p = p->prev;
        q = q->prev;
    }

    if (N1->decimal > 0)
    {
        Nsub->decimal = N1->decimal;
        Nsub->integer = Nsub->integer - Nsub->decimal;
    }

    if (flag)
    { // Swaps the both number again
        swap_Number(N1, N2);
        if (Nsub->sign == 0)
            Nsub->sign = 1;
        else
            Nsub->sign = 0;
    }

    return Nsub;
}

/* Takes argument as Num pointer of 2 Numbers
 * multipy 2 Numbers
 * Returns Nmul
 * Here 1st Number is multiplied by individual by single digit of 2nd Number
 * This is added to Nmul
 */
Num *multiply(Num *N1, Num *N2)
{
    if (!N1 || !N2)
        return NULL;

    Num *Nmul, *M1;
    Nmul = (Num *)malloc(sizeof(Num));
    M1 = (Num *)malloc(sizeof(Num));
    init(Nmul);

    if (zero_Number(N1) == 0 || zero_Number(N2) == 0)
        return Nmul;

    int d1 = N1->decimal, d2 = N2->decimal;

    node *q = N2->tail;

    int k = 0;

    while (q)
    {
        M1 = mul_fun(N1, q->data, k);
        Nmul = add(Nmul, M1);
        q = q->prev;
        k++;
    }

    if (d1 == -1 && d2 == -1)
        Nmul->decimal = -1;
    else if (d1 == -1)
    {
        Nmul->decimal = d2;
        Nmul->integer = Nmul->integer - d2;
    }
    else if (d2 == -1)
    {
        Nmul->decimal = d1;
        Nmul->integer = Nmul->integer - d1;
    }
    else
    {
        Nmul->decimal = d1 + d2;
        Nmul->integer = Nmul->integer - Nmul->decimal;
    }

    if (N1->sign != N2->sign)
        Nmul->sign = 1;

    delete_zeros_of_both_sides(Nmul);

    return Nmul;
}

/* Takes arguments as Num pointer char data and int K
 * Here Num is multiplied by char i.e, single digit
 * K is for appending required zeros while multipying by its place value
 * Returns Num M ( Multiplication of Num N1 and char data )
 */
Num *mul_fun(Num *N1, char data, int k)
{
    if (!N1)
        return NULL;
    Num *M;
    M = (Num *)malloc(sizeof(Num));
    init(M);

    node *p = N1->tail;

    char ch;
    int carry = 0, i;

    for (i = 0; i < k; i++)
        push(M, '0');

    while (p)
    {
        ch = (p->data - 48) * (data - 48) + carry;
        carry = ch / 10;
        ch = ch % 10 + 48;
        push(M, ch);
        p = p->prev;
    }

    if (carry > 0)
    {
        carry = carry + 48;
        push(M, carry);
    }

    return M;
}

/* Takes argument as Num pointer of 2 Numbers
 * Divides 2 Numbers
 * Returns Ndiv
 * It always returns quotient in integer form
 * If any Number is float though it returns solution in complete form only i.e, in integer form
 */
Num *divide(Num *N1, Num *N2, int scale)
{
    if (scale < 0)
        scale = 0;

    if (!N1 || !N2)
        return NULL;

    delete_zeros_of_both_sides(N1);
    delete_zeros_of_both_sides(N2);

    Num *Ndiv;
    Ndiv = (Num *)malloc(sizeof(Num));
    init(Ndiv);

    if (N1->integer + scale < N2->integer)
        return Ndiv;

    Num num1 = *N1, num2 = *N2;
    adjust_Number(&num1, &num2);

    int i;

    if (zero_Number(N2) == 0)
    {
        printf("Operation Cannot be performed..!!\n");
        return NULL;
    }
    else if (zero_Number(N1) == 0)
        return Ndiv;

    for (i = 0; i < scale; i++)
        append(&num1, '0');

    if (num1.decimal > -1)
    {
        num1.integer = num1.integer + num1.decimal;
        num1.decimal = -1;
    }
    if (num2.decimal > -1)
    {
        num2.integer = num2.integer + num2.decimal;
        num2.decimal = -1;
    }

    pop_starting_zeros(&num2);

    Num *a, *mul;
    a = (Num *)malloc(sizeof(Num));
    mul = (Num *)malloc(sizeof(Num));
    init(a);
    char ch;

    node *p = num1.head, *q = num2.head;
    while (q->next)
    {
        append(a, p->data);
        p = p->next;
        q = q->next;
    }

    while (p)
    {
        append(a, p->data);

        for (ch = '9'; ch >= '0'; ch--)
        {
            init(mul);
            mul = mul_fun(&num2, ch, 0);
            if (compare(mul, a) == 0 || compare(mul, a) == -1)
            {
                append(Ndiv, ch);
                ch = 0;
            }
        }
        a = sub(a, mul);
        p = p->next;
    }

    if (Ndiv->integer >= scale)
    {
        Ndiv->integer = Ndiv->integer - scale;
        Ndiv->decimal = scale;
    }
    else
    {
        for (i = 0; i < scale - Ndiv->integer; i++)
            push(Ndiv, '0');
        push(Ndiv, '.');
    }
    delete_zeros_of_both_sides(Ndiv);
    return Ndiv;
}

/* Takes argument as Num pointer of 2 Numbers
 * Returns modula of two numbers
 */
// Num *modula(Num *N1, Num *N2)
// {
//     if (!N1 || !N2)
//         return NULL;

//     Num *Nmod, *Ndiv, *Nmul;
//     Nmod = (Num *)malloc(sizeof(Num));
//     Ndiv = (Num *)malloc(sizeof(Num));
//     Nmul = (Num *)malloc(sizeof(Num));
//     init(Nmod);

//         delete_zeros_of_both_sides(N1);
//     delete_zeros_of_both_sides(N2);

//     //if( N1->decimal > 0 || N2->decimal > 0 )
//     //    return Nmod ;

//     Ndiv = divide(N1, N2, 0);
//     Nmul = multiply(N2, Ndiv);
//     Nmod = sub(N1, Nmul);

//     delete_zeros_of_both_sides(Nmod);
//     return Nmod;
// }

Num *square(Num *N)
{
    if (!N)
        return NULL;

    Num *Nsq;
    Nsq = (Num *)malloc(sizeof(Num));
    init(Nsq);
    Nsq = multiply(N, N);
    return Nsq;
}

Num *power(Num *N1, Num *N2)
{
    if (!N1 || !N2)
        return NULL;

    Num *Npow = (Num *)malloc(sizeof(Num));
    init(Npow);
    if (zero_Number(N1) == 0)
    {
        append(Npow, '0');
        return Npow;
    }

    delete_zeros_of_both_sides(N1);
    delete_zeros_of_both_sides(N2);

    int flag = 0;
    if (N2->sign == 1)
    {
        N2->sign = 0;
        flag = 1;
    }

    if (N2->decimal > 0)
    {
        printf("Runtime warning, Non-zero scale in Exponent..!!\n");
        while (N2->decimal)
            del(N2);
    }

    append(Npow, '1');
    if (zero_Number(N2) == 0)
        return Npow;

    Num S;
    init(&S);
    append(&S, '1');

    while (zero_Number(N2) != 0)
    {
        Npow = multiply(N1, Npow);
        N2 = sub(N2, &S);
    }

    if (flag)
        Npow = divide(&S, Npow, 30);

    return Npow;
}
