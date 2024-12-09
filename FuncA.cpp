#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <cstring>
#include "FuncA.h"
#include <algorithm>

FuncA::FuncA() {
}

double FuncA::Calculate(double x, int terms) {
    double sum = 0.0;
    for (int n = 0; n < terms; ++n) {
        double numerator = pow(-1, n) * tgamma(2 * n + 1); // (2n)! = Gamma(2n+1)
        double denominator = (1 - 2 * n) * pow(4, n) * pow(x, n);
        sum += numerator / denominator;
    }
    return sum;
}

void FuncA::TestServer() {
    

    constexpr int depthOfCalculations = 10;
    constexpr double inputValue = 1.0;

    std::vector<double> data;

    // Starting timer
    auto t1 = std::chrono::high_resolution_clock::now();

    // Value generation
    for (int count = 0; count < 100000; ++count) {
        data.push_back(Calculate(inputValue,depthOfCalculations));
    }

    // Repeating sorting
    for (int repeat = 0; repeat < 4000; ++repeat) {
        std::partial_sort(data.begin(), data.end(), data.end(), [](double left, double right) {
            return std::fabs(left) < std::fabs(right);
        });
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    int iMS = int_ms.count();

    // JSON-formatted output
    std::cout << "{" << std::endl;
    std::cout << "  \"status\": \"success\"," << std::endl;
    std::cout << "  \"time_elapsed_ms\": " << iMS << "," << std::endl;
    std::cout << "  \"data_sample\": ["; 

    // Output first 10 values of data as a sample
    for (size_t i = 0; i < std::min(data.size(), size_t(10)); ++i) {
        std::cout << data[i];
        if (i < 9 && i < data.size() - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "]" << std::endl;
    std::cout << "}" << std::endl;

}

