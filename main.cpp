#include <iostream>
#include "FuncA.h"

int main(){
    double x;
    int terms;
    FuncA funcA;

    std::cout << "Введіть значення x (|x| < 1): ";
    // Зчитування х
    std::cin >> x;
    if (std::abs(x) >= 1) {
        std::cout << "Значення x повинно бути в межах (-1, 1)!" << std::endl;
        return 1;
    }

    std::cout << "Введіть кількість членів ряду для обчислення: ";
    // Зчитування terms 
    std::cin >> terms;

    double result = funcA.Calculate(x, terms);
    // Виведення результату
    std::cout << "Сума ряду: " << result << std::endl;

    return 0;
}

