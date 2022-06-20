typedef struct node
{
    struct node *prev;
    char data;
    struct node *next;
} node;

typedef struct Num
{
    node *head;
    node *tail;
    int sign;    // 0 means +ve and 1 means -ve
    int integer; // length of the number
    int decimal;
} Num;

void init(Num *N);
void append(Num *N, char ch);
void traverse(Num *N);
void adjust_Number(Num *N1, Num *N2);
void swap_Number(Num *N1, Num *N2);
void push(Num *N, char ch);
void pop(Num *N);
int zero_Number(Num *N);
int compare(Num *N1, Num *N2);
void pop_starting_zeros(Num *N);
void del_last_zeros(Num *N);
void delete_zeros_of_both_sides(Num *N);
void del(Num *N);