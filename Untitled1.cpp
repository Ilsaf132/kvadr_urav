#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "unit_tests.h"

const double zer0 = 1e-10;

int RTests(struct Test);
void OutputSolution(struct Results urav);
void LineUrav(struct Koeff sq, struct Results* ptr_urav);
double Discr(struct Koeff sq);
void SolveSquare(struct Koeff sq, struct Results* ptr_urav);
int CheckingTests();
int EndOfStdin(char ch);
int input(struct Koeff* sq);
double abss(double x);
int CheckConditionOfTests (struct Results test_res, struct Test pr);
int CheckMassive(struct Test tests[], int sz_test);
int ComparisonZero(double x);

enum constants {
    error_right = 1,
    error_false = 0,
};

int main ()
{
    struct Koeff sq = {0, 0, 0};
    struct Results urav = {0, 0, 0};
    //#define Tests_or_prog
    #ifndef Tests_or_prog
    if(CheckingTests()){
        printf("Все тесты успешно пройдены!\n");
        txSetConsoleAttr(FOREGROUND_WHITE);
        return 0;
    } else {
        txSetConsoleAttr(FOREGROUND_WHITE);
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
/**
* @brief Функция ввода коэффициентов
* @param ptr_sq Адрес структуры, содержащей коэффициенты
* @return Корректность/некорректность входных данных
*/
int input(struct Koeff* ptr_sq)
{
    assert(ptr_sq!= NULL);
    printf("Введите коэффициенты\n");
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
            printf("Данные некорректны. Программа завершена\n");
            return error_false;
        }

        printf("Введите ещё раз\n");
    }
    return error_right;
}

/**
* @brief Функция - решение квадратного уравнения
* @param sq  [in] Структура с коэффициентами
* @param ptr_urav [out] Адрес структуры с результатами
* @return Количество решений уравнения
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
                ptr_urav -> x1 = ptr_urav -> x2 = (-sq.b)/(2*(sq.a));
            } else {
                ptr_urav -> x1 = ptr_urav -> x2 = 0;
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
* @brief Функция,содержащая тесты
* @return Передача данных теста в функцию проверки
*/
int CheckingTests()
{
    return CheckMassive(tests,SZ_TEST);
}

/**
* @brief Функция, передающая тесты на проверку
* @param tests Массив, содержащий структуру с данными тестов
* @param sz_test Количество тестов
* @return Правильность работы теста
*/
int CheckMassive(struct Test tests[], int sz_test)
{
     for (int i = 0; i < sz_test; ++i) {
        if (!RTests(tests[i])) {
            return error_false;
        }
     }
     return error_right;
}

/**
* @brief Функция проверки теста
* @param pr Структура теста
* @return Правильность/неправильность теста
*/
int RTests(struct Test pr)
{
    struct Results test_res = {0,0,0};
    SolveSquare(pr.kfTest,&test_res);
    if (CheckConditionOfTests(test_res, pr))
    {
        txSetConsoleAttr(FOREGROUND_RED);
        printf("ERROR TEST %d. a = %lf, b = %lf, c = %lf ", pr.nTest,pr.kfTest.a,pr.kfTest.b,pr.kfTest.c);
        printf("x1 = %lf, x2 = %lf, numb_Roots = %d\n", test_res.x1,test_res.x2,test_res.nRoots);
        printf("Expected: x1 = %lf, x2 = %lf, numb_Roots = %d\n", pr.param.x1, pr.param.x2, pr.param.nRoots);
        return error_false;
    } else {
        txSetConsoleAttr(FOREGROUND_GREEN);
        printf("Test №%d успешно пройден!\n", pr.nTest);
        return error_right;
    }

}

/**
* @brief Функция, проверяющая совпадение полученных результатов с тестовыми
* @param test_res Структура с результатами
* @param pr Структура с тестовыми данными
* @return Совпадение полученных данных с тестовыми
*/
int CheckConditionOfTests (struct Results test_res, struct Test pr)
{
    return test_res.nRoots != pr.param.nRoots || (test_res.x1 != pr.param.x1 && test_res.x2 != pr.param.x2
    && test_res.x1 != pr.param.x2 && test_res.x2 != pr.param.x1);
}

/**
* @brief Функция вывода решений
* @param urav Структура с полученными результатами решений
*/
void OutputSolution(struct Results urav)
{
    switch(urav.nRoots)
    {
        case 0:
            printf("Нет решений\n");
            break;
        case 1:
            printf("x = %lf\n", urav.x1);
            break;
        case 2:
            printf("x1 = %lf, x2 = %lf\n", urav.x1, urav.x2);
            break;
        case EXCEPT_ANS:
            printf("Любое число\n");
            break;
        default:
            printf("ERROR");
    }
}

/**
* @brief Функция решения линейного уравнения
* @param sq Структура, содержащая коэффициенты
* @param ptr_urav Адрес структуры с корнями и количеством
* @return Количество решений линейного уравнения
*/
void LineUrav(struct Koeff sq, struct Results* ptr_urav)
{
    assert(ptr_urav != NULL);
    if (ComparisonZero(sq.b)) {
            ptr_urav -> nRoots = (ComparisonZero(sq.c))? EXCEPT_ANS : 0;
    } else {
        if (!ComparisonZero(sq.c)) {
            ptr_urav -> x1 = ptr_urav -> x2 = -sq.c/sq.b;
        } else {
            ptr_urav -> x1 = ptr_urav -> x2 = 0;
        }
        ptr_urav -> nRoots = 1;
    }
}

/**
* @brief Функция модуля числа
* @param x Число
* @return Модуль числа
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
* @brief Проверка правильности ввода
* @param ch Проверяемый символ
* @return Корректность/некорректность ввода
*/
int EndOfStdin(char ch)
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

/**
* @brief Функция Дискриминанта
* @param sq Структура с коэффициентами уравнения
* @return Формула Дискриминанта
*/
double Discr(struct Koeff sq)
{
    return sq.b*sq.b - 4*sq.a*sq.c;
}

/**
* @brief Сравнение числа double с нулем
* @param x Полученное число
* @return Равенство числа нулю
*/
int ComparisonZero(double x)
{
    return (abss(x) <= zer0);
}
