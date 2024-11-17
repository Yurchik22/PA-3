#include "FuncA.h"
#include <cmath>

FuncA::FuncA(){
}

double FuncA::Calculate(double x, int terms){
    double sum = 0.0;
    for (int n = 0; n < terms; ++n) {
        double numerator = pow(-1, n) * tgamma(2 * n + 1); // (2n)! = Gamma(2n+1)
        double denominator = (1 - 2 * n) * pow(4, n) * pow(x, n); 
        sum += numerator / denominator;
    }
    return sum;
}

