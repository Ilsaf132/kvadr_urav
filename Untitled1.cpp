#include <TXlib.h>
#include <stdio.h>
#include <math.h>
main ()
{
    float a,b,c;
    scanf("%f %f %f",&a,&b,&c);
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("infinite");
            } else {
                printf("нет корней");
            }
        } else {
            printf("%g", -c/b);
        }
    } else {
        float D,x1,x2;
        D = b*b - 4*a*c;
        if (D < 0) {
            printf("корней нет");
        } else if (D == 0) {
            printf("%g", -b/(2*a));
        } else if (D > 0) {
            x1 = (-b + sqrt(D))/(2*a);
            x2 = (-b - sqrt(D))/(2*a);
            printf("%g %g", x1,x2);
        }
    }
}
