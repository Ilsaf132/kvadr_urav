/*!
\file
\brief ��������������� �����-������

������ ���� �������� � ���� �������, ��������������� ���� � ����� ���������� ������.
*/
#include "inp_out.h"
#include "unit_tests.h"
#include "cons.h"
#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
/**
* @brief ������� ����� �������������
* @param ptr_sq ����� ���������, ���������� ������������
* @return ������������/�������������� ������� ������
*/
int input(struct Koeff* ptr_sq)
{
    assert(ptr_sq!= NULL);
    printf("������� ������������\n");
    int t = 0;
    while ((t = scanf("%lf %lf %lf", &ptr_sq->a, &ptr_sq->b, &ptr_sq->c)) != 3 ||
    !EndOfStdin(getchar()))
    {
        int ch = getchar();
        while(ch != '\n' && ch != EOF)
        {
            ch = getchar();
        }
        if (ch == EOF)
        {
            printf("������ �����������. ��������� ���������\n");
            return error_false;
        }

        printf("������� ��� ���\n");
    }
    return error_right;
}


/**
* @brief ������� ������ �������
* @param urav ��������� � ����������� ������������ �������
*/
void OutputSolution(struct Results urav)
{
    switch(urav.nRoots)
    {
        case 0:
            printf("��� �������\n");
            break;
        case 1:
            printf("x = %lf\n", urav.x1);
            break;
        case 2:
            printf("x1 = %lf, x2 = %lf\n", urav.x1, urav.x2);
            break;
        case EXCEPT_ANS:
            printf("����� �����\n");
            break;
        default:
            printf("ERROR");
    }
}

/**
* @brief �������� ������������ �����
* @param ch ����������� ������
* @return ������������/�������������� �����
*/
int EndOfStdin(int ch)
{
    while (ch != EOF && ch != '\n')
    {
        if (ch == ' ') {
            ch = getchar();
        } else {
            return 0;
        }

    }
    return 1;
}
