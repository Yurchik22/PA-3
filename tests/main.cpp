#include <iostream>
#include <cmath>
#include <complex>

using namespace std;


bool verifySqrtSeries(double x, int terms, double expected_result) {
    double result = 1.0;
    double term = 1.0;

    for (int n = 1; n < terms; ++n) {
        term *= (-1) * (2 * n - 2) * (2 * n - 1) / (4.0 * n * (2 * n + 1)) * x;
        result += term;
    }

    return fabs(result - expected_result) < 1;
}

int main() {
  
    double x = 0.1; 
    int terms = 5;  

    double expected_result = sqrt(1 + x);

    if (verifySqrtSeries(x, terms, expected_result)) {
        cout << "The series sum is correct!" << endl;
        return 0; 
    } else {
        cout << "The series sum is incorrect!" << endl;
        return 1; 
    }
}

