#include <iostream>
#include "Converter.h"

int main() {
    Converter converter;
    std::cout << converter.toIEEEFloatBin(3.375)<<'\n';
    //std::cout << converter.toFloat("1")<<'\n';
    std::cout << converter.toFloat(converter.toIEEEFloatBin(3.375))<<'\n';
    return 0;
}
