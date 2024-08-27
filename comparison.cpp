/*!
\file
\brief ������� ��������� ���������� ������

������ ���� �������� � ���� �������, ����������� ��� ��������� ������ � �� �������.
*/
#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "comparison.h"
#include "cons.h"
#include "unit_tests.h"


/**
* @brief ������� ������ �����
* @param x �����
* @return ������ �����
*/
double abss(double x)
{
    if (x < 0) {
        return (-x);
    } else {
        return x;
    }

}

/**
* @brief ��������� ����� double � �����
* @param x ���������� �����
* @return ��������� ����� ����
*/
int ComparisonZero(double x)
{
    return (abss(x) <= zer0);
}
/**
* @brief ��������� ���� ����� ���� double � NAN
* @param a ������ ���������� �����
* @param b ������ ���������� �����
* @return ��������� ���������(1 - �����, 0 - �� �����)
*/
int ComparisonNumb(double a, double b)
{
    switch(IsNan(a) + IsNan(b)) {
        case 0: return error_right;
                break;
        case 1: return error_false;
                break;
        default: return CompareNotNan(a,b);
    }
}

/**
* @brief ������ �������� ���������� -c � -e ��� ����� � �������
* @param str ������-��������
* @return ������������ �������� � ����������� �� ���������
*/
int ChooseNumb(char* str) {
    if (!strcmp(str,"1")) {
        return error_right;
    } else if (!strcmp(str,"0")) {
        return error_false;
    } else {
        return EXCEPT_ANS;
    }
}


/**
* @brief ��������� ���� ����� double
* @param a ������ �����
* @param b ������ �����
* @return ��������� ���������
*/
int CompareNotNan(double a, double b) {
    return (abss(a-b) < zer0)? error_right:error_false;
}

/**
* @brief �������� ����� �� NAN ��� INF
* @param x ���������� �����
* @return ��������� ����� NAN ��� INF
*/
int IsNan(double x) {
    return isfinite(x);
}
