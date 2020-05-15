//
// Created by Norman Qining Wen on 15/5/2020.
//

#ifndef FLOATINGCONVERTER_CONVERTER_H
#define FLOATINGCONVERTER_CONVERTER_H
#include <string>

class Converter {
public:
    explicit Converter() = default;
    std::string toIEEEFloatBin(double num);
    double toFloat(const std::string& rep);
private:
    unsigned int findLargestBit(int numIn);
    enum class bit:bool {
        ONE = true, ZERO = false
    };
    char convertChar(const bit&);
    static void toBin(unsigned numIn, std::vector<bit>& container);
    static void toBin(double decimal, std::vector<bit>& container);
    double binStrToNum(const std::string& in);
    double mantissaToNum(const std::string& in);
};


#endif //FLOATINGCONVERTER_CONVERTER_H
