/*!
\file
\brief ������� ������ � ��������

������ ���� �������� � ���� �������, ����������� ��� ������ � ��������
*/
#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "unit_tests.h"
#include "solve_sq.h"
#include "comparison.h"
#include "inp_out.h"
#include "cons.h"

/**
* @brief ������� ������ � ����, ������� ������ � ����������� ������� -c � -e � ����������� �� ����� � �������
* @param argv ������ �����, ��������� � �������
* @param argc ���������� �����, ��������� � �������
* @param clr ������ �� ����������, �� �������� ������� ������� ���� ������ ������
* @param e_res ������ �� ����������, �� �������� ������� ������� ������� ������ ������
* @return ��������� ����� ����
*/
int IfColorAndResults(char* argv[], int argc, int* clr, int* e_res)
{
    assert(argv != NULL);
    bool one_color = true, one_res = true;
    for(int i = 1; i < argc; ++i) {
        if (!(strcmp(argv[i], "-c")) && one_color && NeededSize(argc))  {
            *clr = ChooseNumb(argv[i+1]);
            i += 1;
            one_color = false;
        } else if (!(strcmp(argv[i], "-e")) && one_res && NeededSize(argc)) {
            *e_res = ChooseNumb(argv[i+1]);
            i += 1;
            one_res = false;
        } else if(!(strcmp(argv[i], "--help")) && i == 1 && (argc == 4 || argc == 2)) {
            return HelpDecisions(argv[i+1], argv[i+2], argc);
        } else {
            return error_false;
        }
    }

    return error_right;

}
/**
* @brief ������� ������ ������ ���������� � �������� -c � -e � ����������� �� ����������� ��������� ����� --help � �������
* @param argv ������, ���������� ������� ����� --help
* @param clr �������� ���������� ������
* @param argc ���������� �����, ��������� � �������
* @return ��������� ����� ����
*/
int HelpDecisions(char* str, char* arg, int argc) {
    if (argc == 2) {
      printf("-c 1 - ������� ���������� ���������� ����� � �������, � ������������ - � �������\n");
      printf("-c 0 - ���� ������ ��� ������ ������ ������� ����������\n");
      printf("-e 1 - ��������� ���������� ��� ������ �� ���������� ������\n");
      printf("-e 0 - ������ ������� ���������� ������ ��������� �� �����");
      return PRINT_HELP;
    } else if (!strcmp(str, "-c") && !strcmp(arg,"1")) {
        printf("������� ���������� ���������� ����� � �������, � ������������ - � �������");
        return PRINT_HELP;
    } else if (!strcmp(str, "-c") && !strcmp(arg,"0")) {
        printf("���� ������ ��� ������ ������ ������� ����������");
        return PRINT_HELP;
    } else if (!strcmp(str, "-e") && !strcmp(arg,"1")) {
        printf("��������� ���������� ��� ������ �� ���������� ������");
        return PRINT_HELP;
    } else if (!strcmp(str, "-e") && !strcmp(arg, "0")) {
        printf("������ ������� ���������� ������ ��������� �� �����");
        return PRINT_HELP;
    } else {
        return error_false;
    }
}

/**
* @brief ����������� argc ���������, ��� ������ �������
* @param argc ������, ���������� ������� ����� --help
* @return �������� �� argc ����������� ���������
int NeededSize(int argc){
    return (argc == 3 || argc == 5);
}
