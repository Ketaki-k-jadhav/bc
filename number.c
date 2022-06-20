#include "number.h"
/* Takes argument as Num pointer
 * Initializes Number data type
 * Initializes head and tail pointer to NULL
 */
void init(Num *N)
{
    N->head = NULL;
    N->tail = NULL;
    N->sign = 0;
    N->integer = 0;
    N->decimal = -1;
}

/* Takes argument as Num pointer and char data to be inserted
 * Append the node at last
 * If decimal = -1, then append node integer++
 * If decimal >= 0, means of float type, decimal++
 * If we append '.' then initialize decimal to -1
 */
void append(Num *N, char ch)
{
    if (ch == '.')
    {
        if (N->decimal > -1)
        { // Here Number already contains '.' so again it does not append '.' and returns
            printf("Invalid Number...!!!");
            return;
        }
        N->decimal = 0;
        return;
    }

    node *newnode;
    newnode = (node *)malloc(sizeof(node));
    if (!newnode)
        return;
    newnode->data = ch;
    newnode->next = NULL;
    newnode->prev = NULL;

    if (!N->head)
    { //Head is pointing to NULL means Num is empty
        N->head = newnode;
        N->tail = newnode;
        if (N->decimal == 0)
            N->decimal++;
        else
            N->integer++;
        return;
    }
    newnode->prev = N->tail;
    N->tail->next = newnode;
    N->tail = newnode;
    if (N->decimal > -1)
    {
        N->decimal++;
    }
    else
    {
        N->integer++;
    }
}

/* Prints the Number
 * If Number is NULL prints 0
 * Prints negative sign ( - ) if Number sign value 1 otherwise do not print
 * Prints the number as per Number integer length and decimal length
 * While printing integer part gives comma after 3 digits considering from decimal point (.)
 */
void traverse(Num *N)
{
    if (!N)
        return;
    node *p = N->head;
    int i = N->integer, d = N->decimal, s = N->sign;
    int j = 0, comma = i;
    if (s)
        printf("-");
    if (!i)
        printf("0");
    while (p && j < i)
    {
        printf("%c", p->data);
        p = p->next;
        j++;
        comma--;
    }
    if (d > 0)
    {
        j = 0;
        printf(".");

        while (p && j < d)
        {
            printf("%c", p->data);
            p = p->next;
            j++;
        }
    }
    printf("\n");
    return;
}

void push(Num *N, char ch)
{
    if ((ch < '0' || ch > '9') && ch != '.')
        return;
    if (ch == '.')
    {
        if (N->decimal > -1)
        {
            printf("Invalid Number...!!");
            return;
        }
        N->decimal = N->integer;
        N->integer = 0;
        return;
    }

    node *newnode;
    newnode = (node *)malloc(sizeof(node));
    if (!newnode)
        return;
    newnode->data = ch;
    newnode->next = NULL;
    newnode->prev = NULL;

    if (!N->head)
    { //Head is pointing to NULL means Num is empty
        N->head = newnode;
        N->tail = newnode;
        N->integer++;
        return;
    }

    newnode->next = N->head;
    N->head->prev = newnode;
    N->head = newnode;
    N->integer++;

    return;
}

void pop(Num *N)
{
    if (N->integer == 0 && (N->decimal == 0 || N->decimal == -1))
        return;

    if (N->integer == 1 && N->decimal <= 0)
    {
        init(N);
        return;
    }
    else if (N->integer == 0 && N->decimal == 1)
    {
        init(N);
        return;
    }

    if (N->integer > 0)
        N->integer--;
    else if (N->decimal > -1)
        N->decimal--;
    node *p = N->head;
    N->head = p->next;
    N->head->prev = NULL;
    free(p);
    return;
}

void del(Num *N)
{
    if (N->integer == 0 && (N->decimal == 0 || N->decimal == -1))
        return;

    if (N->integer == 1 && N->decimal <= 0)
    {
        init(N);
        return;
    }
    else if (N->integer == 0 && N->decimal == 1)
    {
        init(N);
        return;
    }
    node *q = N->tail;
    N->tail = q->prev;
    N->tail->next = NULL;
    free(q);
    if (N->decimal > 0)
        N->decimal--;
    else
        N->integer--;
    return;
}

void adjust_Number(Num *N1, Num *N2)
{
    int d1, d2, l1, l2, i;
    d1 = N1->decimal;
    d2 = N2->decimal;
    l1 = N1->integer;
    l2 = N2->integer;

    if (d1 > -1 || d2 > -1)
    {
        if (d1 == d2)
            ;
        else if (d1 > d2)
        {
            if (d2 == -1)
            {
                d2 = 0;
                N2->decimal = 0;
            }
            for (i = 0; i < d1 - d2; i++)
                append(N2, '0');
        }
        else
        {
            if (d1 == -1)
            {
                d1 = 0;
                N1->decimal = 0;
            }
            for (i = 0; i < d2 - d1; i++)
                append(N1, '0');
        }
    }
    if (l1 > l2)
        for (i = 0; i < l1 - l2; i++)
            push(N2, '0');

    else if (l2 > l1)
    {
        for (i = 0; i < l2 - l1; i++)
            push(N1, '0');
    }
}

void swap_Number(Num *N1, Num *N2)
{
    Num tmp = *N1;
    *N1 = *N2;
    *N2 = tmp;
    return;
}

int zero_Number(Num *N)
{
    node *p = N->head;
    while (p)
    {
        if (p->data != '0')
            return 1;
        p = p->next;
    }
    return 0;
}

void pop_starting_zeros(Num *N)
{
    if (N->integer == 0)
        return;
    while (N->integer && N->head && N->head->data == '0')
        pop(N);
    return;
}

int compare(Num *N1, Num *N2)
{
    pop_starting_zeros(N1);
    pop_starting_zeros(N2);
    int i1 = N1->integer, i2 = N2->integer;

    if (i1 > i2)
        return 1;
    else if (i1 == i2)
    {
        node *p = N1->head, *q = N2->head;
        int d1 = N1->decimal, d2 = N2->decimal;
        int j;
        if (d1 > d2)
        {
            if (d2 == -1)
            {
                append(N2, '.');
                d2 = 0;
            }
            for (j = 0; j < d1 - d2; j++)
                append(N2, '0');
        }
        else if (d2 > d1)
        {
            if (d1 == -1)
            {
                append(N1, '.');
                d1 = 0;
            }
            for (j = 0; j < d2 - d1; j++)
                append(N1, '0');
        }

        while (p && q)
        {
            if (p->data > q->data)
                return 1;
            if (p->data < q->data)
                return 0;
            p = p->next;
            q = q->next;
            i1--;
        }
        return -1;
    }
    else
        return 0;
}

/* Deletes unnecessary last zeros
 * Deletes only decimal part zeros
 * Do not delete zeros of integer part
 */

void del_last_zeros(Num *N)
{
    if (N->decimal == -1)
        return;
    while (N->decimal && N->tail && N->tail->data == '0')
    {
        del(N);
    }
    return;
}

//Deletes unnecessary zeros on both sides
void delete_zeros_of_both_sides(Num *N)
{
    pop_starting_zeros(N);
    del_last_zeros(N);
    return;
}
