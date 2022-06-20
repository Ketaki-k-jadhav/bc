#include "getnext.h"

// t[j].type=100, for integer token
// t[j].type=200, for character operator token
// t[j].type=300, for space
// t[j].type=400, for possible errors
// t[j].type=500, for end of expression
// flag==-1 indicates error

int i = 0;

Num *N;
int getnext(char expr[], token t[])
{

    static int j = 0;
    int count = 0;
    int flag;
    if (isdigit(expr[0]) || expr[0] == '(')
    {
        while (expr[i] != '\0')
        {

            switch (expr[i])
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                t[j].type = 100;
                N = (Num *)malloc(sizeof(Num));
                init(N);
                while (isdigit(expr[i]) || expr[i] == '.')
                {
                    append(N, expr[i]);
                    i++;
                }
                t[j].data.num = N;
                if (t[j].type == 100 && t[j - 2].type == 100)
                {
                    printf("Invalid, check the operators.\n");
                    flag = -1;
                    return flag;
                }
                i--;

                break;

            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                t[j].type = 200;
                t[j].data.op = expr[i];
                if (t[j].type == 200 && t[j - 2].type == 200)
                {

                    printf("Operator '%c'followed by another operator '%c' is not valid.\n", t[j - 2].data.op, t[j].data.op);
                    flag = -1;
                    return flag;
                }

                break;
            case '(':
            case ')':
                t[j].data.op = expr[i];
                count++;
                if (t[j].data.op == '(' && t[j - 2].type != 200 && j != 0)
                {
                    printf("Expected operator before '('\n");
                    flag = -1;
                    return flag;
                }
                if (t[j].data.op == ')' && expr[i + 1] == ' ' && t[j + 2].type != 200)
                {
                    printf("Expected operator after ')'\n");
                    flag = -1;
                    return flag;
                }
                break;
            case ' ':
                t[j].type = 300;
                break;
            default:
                flag = -1;
                printf("Invalid input\n");
                return flag;
                break;
            }
            i++;

            j++;
        }
        t[j].type = 500;
        switch (expr[i - 1])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ')':
            break;
        default:
            printf("Expression cannot end with '%c'.\n", expr[i - 1]);
            flag = -1;
            return flag;
            break;
        }

        if (count % 2 != 0)
        {
            printf("Imbalanced  parentheses\n");
            flag = -1;
            return flag;
        }
    }
    else
    {
        flag = -1;
        printf("Expression cannot start with '%c'.\n", expr[0]);
        return flag;
    }
}
