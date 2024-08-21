#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

const int Except_ans = -1;
const double zer0 = 0.000001;
void output(int numb_Roots, double x1, double x2)
{
    switch(numb_Roots)
    {
        case 0:
            printf("Нет решений\n");
            break;
        case 1:
            printf("x = %lf\n", x1);
            break;
        case 2:
            printf("x1 = %lf, x2 = %lf\n", x1, x2);
            break;
        case Except_ans:
            printf("Любое число\n");
            break;
        default:
            printf("ERROR");
    }
}


int line_urav(double b, double c, double* x1)
{
    assert(x1 != NULL);
    if (abs(b) <= zer0) {
            return (abs(c) <= zer0)? Except_ans : 0;
    } else {
            *x1 = -c/b;
            return 1;
    }
}

double Discr(double a, double b, double c)
{
    double D = 0;
    D = b*b - 4*a*c;
    return D;
}

int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    if (abs(a) <= zer0) {
        return line_urav(b, c, x1);
    } else {
        double D = 0, sqr_d = 0;
        D = Discr(a, b, c);
        if (abs(D) <= zer0) {
            *x1 = *x2 = -b/(2*a);
            return 1;
        } else if (D > 0) {
            sqr_d = sqrt(D);
            *x1 = (-b + sqr_d)/(2*a);
            *x2 = (-b - sqr_d)/(2*a);
            return 2;
        } else {
            return 0;
        }
    }
}

int main ()
{
    double a = 0, b = 0, c = 0;
    int numb_Roots = 0, ent = 0;
    double x1 = 0, x2 = 0;
    printf("Введите коэффициенты\n");
    while(scanf("%lf %lf %lf", &a, &b, &c) != 3)
    {
        char ch = getchar();
        while(ch != '\n' or ch != EOF);
        printf("Введите ещё раз\n");
    }

    numb_Roots = SolveSquare(a, b, c, &x1, &x2);
    output(numb_Roots, x1, x2);
    return 0;
}
