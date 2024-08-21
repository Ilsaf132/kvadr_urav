    #include <TXLib.h>
    #include <stdio.h>
    #include <math.h>
    #include <float.h>

    const int Except_ans = -1;
    const double zer0 = 0.000001;

    int RTests(struct Test);
    void OutputSolution(struct Results urav);
    int LineUrav(struct Koeff sq, struct Results* ptr_urav);
    double Discr(struct Koeff sq);
    int SolveSquare(struct Koeff sq, struct Results* ptr_urav);
    int CheckingTests();
    int EndOfStdin(char ch);
    void input(struct Koeff* sq);
    double abss(double x);
    int ComparisonZero(double x);

    struct Results
    {
        double x1;
        double x2;
        int nRoots;
    };

    struct Koeff
    {
        double a;
        double b;
        double c;
    };

    struct Test
    {
        int nTest;
        struct Koeff kf_test;
        struct Results param;
    };

    int ComparisonZero(double x)
    {
        return (abss(x) <= zer0);
    }
    void input(struct Koeff* ptr_sq)
    {
        assert(ptr_sq!= NULL);
        printf("Введите коэффициенты\n");
        while (scanf("%lf %lf %lf", &ptr_sq->a, &ptr_sq->b, &ptr_sq->c) != 3 || !EndOfStdin(getchar()))
        {
            char ch = getchar();
            while(ch != '\n' && ch != EOF)
            {
                ch = getchar();
            }
            printf("Введите ещё раз\n");
        }
    }

    double abss(double x)
    {
        if (x < 0) {
            return (-x);
        } else {
            return x;
        }
    }
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

    int CheckingTests()
    {   struct Test t1{1,{1,0,-4},{-2,2,2}}; // 2 решения
        struct Test t2{2,{0,0,0},{0,0,Except_ans}};  // любое число
        struct Test t3{3,{1,2,1},{-1,-1,1}}; //  1 решение(дискриминант равен нулю)
        struct Test t4{4,{0,1,2},{-2,-2,1}};   //  1 решение(a = 0)
        struct Test t5{5,{1,-3,2},{1,2,2}};     //  2 решения
        struct Test t6{6,{1,2,3},{0,0,0}}; //нет решений (дискриминант меньше нуля)
        struct Test t7{7,{0,0,3},{0,0,0}}; //нет решений (c != 0)
        struct Test t8{8,{0,1,0},{0,0,1}}; // 1 решение
        struct Test t9{9,{4,0,0},{0,0,1}}; //1 решение(b = 0)
        return RTests(t1) &&
               RTests(t2) &&
               RTests(t3) &&
               RTests(t4) &&
               RTests(t5);
    }

    int RTests(struct Test pr)
    {
        struct Results test_res = {0,0,0};
        struct Results* ptr_test;
        ptr_test = &test_res;
        test_res.nRoots = SolveSquare(pr.kf_test,ptr_test);
        if (test_res.nRoots != pr.param.nRoots || (test_res.x1 != pr.param.x1 && test_res.x2 != pr.param.x2
        && test_res.x1 != pr.param.x2 && test_res.x2 != pr.param.x1))
        {
            printf("ERROR TEST %d. a = %lf, b = %lf, c = %lf ", pr.nTest,pr.kf_test.a,pr.kf_test.b,pr.kf_test.c);
            printf("x1 = %lf, x2 = %lf, numb_Roots = %d\n", test_res.x1,test_res.x2,test_res.nRoots);
            printf("Expected: x1 = %lf, x2 = %lf, numb_Roots = %d\n", pr.param.x1, pr.param.x2, pr.param.nRoots);
            return 0;
        } else {
            return 1;
        }

    }

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
            case Except_ans:
                printf("Любое число\n");
                break;
            default:
                printf("ERROR");
        }
    }


    int LineUrav(struct Koeff sq, struct Results* ptr_urav)
    {
        assert(ptr_urav != NULL);
        if (ComparisonZero(sq.b)) {
                return (ComparisonZero(sq.c))? Except_ans : 0;
        } else {
            if (!ComparisonZero(sq.c)) {
                ptr_urav -> x1 = ptr_urav -> x2 = -sq.c/sq.b;
            } else {
                ptr_urav -> x1 = ptr_urav -> x2 = 0;
            }
            return 1;
        }
    }

    double Discr(struct Koeff sq)
    {
        return sq.b*sq.b - 4*sq.a*sq.c;
    }

    int SolveSquare(struct Koeff sq, struct Results* ptr_urav)
    {
        assert(ptr_urav != NULL);
        if (ComparisonZero(sq.a)) {
            return LineUrav(sq, ptr_urav);
        } else {
            double D = 0, sqr_d = 0;
            D = Discr(sq);
            if (ComparisonZero(D)) {
                if (!ComparisonZero(sq.b)) {
                    ptr_urav -> x1 = ptr_urav -> x2 = (-sq.b)/(2*(sq.a));
                } else {
                    ptr_urav -> x1 = ptr_urav -> x2 = 0;
                }
                return 1;
            } else if (D > 0) {
                if (ComparisonZero(sq.c)) {
                    ptr_urav -> x1 = 0;
                    ptr_urav -> x2 = -sq.b/sq.a;
                } else {
                    sqr_d = sqrt(D);
                    ptr_urav -> x1 = (-sq.b + sqr_d)/(2*sq.a);
                    ptr_urav -> x2 = (-sq.b - sqr_d)/(2*sq.a);
                }
                return 2;
            } else {
                return 0;
            }
        }
    }

    int main ()
    {
        struct Koeff sq = {0, 0, 0};
        struct Koeff *ptr_sq;
        ptr_sq = &sq;
        struct Results urav = {0, 0, 0};
        struct Results* ptr_urav;
        ptr_urav = &urav;
        int ent = 0;
        if (CheckingTests()) {
            input(ptr_sq);
            urav.nRoots = SolveSquare(sq, ptr_urav);
            OutputSolution(urav);
        }
        return 0;
    }
