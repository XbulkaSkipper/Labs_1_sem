#include <stdio.h>
#include <math.h>
#include <windows.h>


int f(int n);
double answer_with_n(double x, int n);
double answer_with_epsilon(double eps, double x);

int main () {
    SetConsoleOutputCP(CP_UTF8);
    int methods;
    double x;

    printf("Enter x: ");
    scanf_s("%lf", &x);
    if(fabs(x) >= 1)
    {
        printf("Error!");
        return 1;
    }

    printf("Enter methods:\n 1)With precision \n 2)With 'n' \n Your selection: ");
    scanf_s("%d", &methods);

    switch(methods)
    {
        case 1:
            double eps;
        printf("Enter precision: ");
        scanf_s("%lf", &eps);
        if(eps<=0 || eps>= 1) {
            printf("Error!");
            return 1;
        }
        double res_1 = answer_with_epsilon(eps, x);
        printf("Result: %lf", res_1);
        break;

        case 2:
            int n;
        double y;
        printf("Enter n: ");
        scanf_s("%lf", &y);
        n = (int)y;
        if (y != n) {
            printf("Error!");
            return 1;
        }
        if(n<0) {
            printf("Error!");
            return 1;
        }
        double res_2 = answer_with_n(x, n);
        printf("Result: %lf", res_2);
        break;

        default:
            printf("Error!");
        return 1;
    }

    return 0;

}

double answer_with_epsilon(double eps, double x)
{
    double previous, current = 1, sum=1;
    int n = 1;
    while(fabs(previous-current) > eps) {
        previous = current;
        current = pow(-1,n)*pow(x,2*n) / f(n);
        sum += current;
        n++;
    }
    return sum;
}

double answer_with_n(double x, int n)
{
    double res = 1;
    double intermediate_result;

    for(int i = 1; i<n; i++)
    {
        intermediate_result = pow(-1,n)*(pow(x,2*n))/f(n);
        res += intermediate_result;
    }
    return res;
}

int f(int n)
{
    int result = 1;
    for(int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}