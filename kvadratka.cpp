#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "unit_tests.h"
#include "solve_sq.h"
#include "comparison.h"
#include "inp_out.h"
#include "cons.h"

int main (int argc, char* argv[])
{
    struct Koeff sq = {0, 0, 0};
    struct Results urav = {0, 0, 0};
    int clr = 0, res = 0;
    //#define Tests_or_prog
    #ifndef Tests_or_prog
    switch(IfColorAndResults(argv,argc, &clr, &res)) {
            case error_right:
                            if(CheckingTests(argv, argc)){
                                printf("��� ����� ������� ��������!\n");
                                txSetConsoleAttr(FOREGROUND_WHITE);
                                return 0;
                            } else {
                                txSetConsoleAttr(FOREGROUND_WHITE);
                                return -1;
                            }
            case PRINT_HELP:
                            return 0;
            default:
                            printf("������ �����");
                            return -1;
    }
    #else
    if (input(&sq)) {
        SolveSquare(sq, &urav);
        OutputSolution(urav);
    } else {
        return -1;
    }
    return 0;
    #endif // Tests_or_prog
}
