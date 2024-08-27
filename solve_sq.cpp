/*!
\file
\brief ������� ����������� ��������� � ������ ����

������ ���� �������� � ���� �������, ����������� ��� ��������� ������ � ���������� �������
����������� ��������� �� ������ ���������� ������.
*/
#include "solve_sq.h"
#include "unit_tests.h"
#include "comparison.h"
#include "cons.h"
#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
/**
* @brief ������� - ������� ����������� ���������
* @param sq  [in] ��������� � ��������������
* @param ptr_urav [out] ����� ��������� � ������������
* @return ���������� ������� ���������
*/
void SolveSquare(struct Koeff sq, struct Results* ptr_urav)
{
    assert(ptr_urav != NULL);
    if (ComparisonZero(sq.a)) {
        LineUrav(sq, ptr_urav);
    } else {
        double D = 0, sqr_d = 0;
        D = Discr(sq);
        if (ComparisonZero(D)) {
            if (!ComparisonZero(sq.b)) {
                ptr_urav -> x1 = (-sq.b)/(2*(sq.a));
            } else {
                ptr_urav -> x1 = 0;
            }
            ptr_urav -> nRoots = 1;
        } else if (D > 0) {
            if (ComparisonZero(sq.c)) {
                ptr_urav -> x1 = 0;
                ptr_urav -> x2 = -sq.b/sq.a;
            } else {
                sqr_d = sqrt(D);
                ptr_urav -> x1 = (-sq.b + sqr_d)/(2*sq.a);
                ptr_urav -> x2 = (-sq.b - sqr_d)/(2*sq.a);
            }
            ptr_urav -> nRoots = 2;
        } else {

            ptr_urav -> nRoots = 0;
        }
    }
}

/**
* @brief ������� ������� ��������� ���������
* @param sq ���������, ���������� ������������
* @param ptr_urav ����� ��������� � ������� � �����������
* @return ���������� ������� ��������� ���������
*/
void LineUrav(struct Koeff sq, struct Results* ptr_urav)
{
    assert(ptr_urav != NULL);
    if (ComparisonZero(sq.b)) {
            ptr_urav -> nRoots = (ComparisonZero(sq.c))? EXCEPT_ANS : 0;
    } else {
        if (!ComparisonZero(sq.c)) {
            ptr_urav -> x1 = -sq.c/sq.b;
        } else {
            ptr_urav -> x1 = 0;
        }
        ptr_urav -> nRoots = 1;
    }
}

/**
* @brief ������� �������������
* @param sq ��������� � �������������� ���������
* @return ������� �������������
*/
double Discr(struct Koeff sq)
{
    return sq.b*sq.b - 4*sq.a*sq.c;
}
