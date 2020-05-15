//
// Created by Norman Qining Wen on 15/5/2020.
//

#include "Converter.h"
#include <cmath>
#include <vector>
#include <bitset>

std::string Converter::toIEEEFloatBin(double num) {
    //first need to convert to binary number
    bool negative = false;
    if (num < 0){
        negative = true;
    }
    double mag = abs(num);
    unsigned whole = floor(mag);
    unsigned int largestBit = findLargestBit(whole);
    double decimal = mag - whole;
    std::vector<bit> wholeDigits;
    wholeDigits.resize(largestBit + 1, bit::ZERO);
    std::vector<bit> decimalDigits;
    toBin(whole, wholeDigits);
    toBin(decimal, decimalDigits);
    int exponent = static_cast<int>(wholeDigits.size())-1; //bias is 127
    if (exponent == 0){
        while (decimalDigits.front() == bit::ZERO){
            exponent--;
            decimalDigits.erase(decimalDigits.begin());
        }
        wholeDigits.pop_back();
        wholeDigits.emplace_back(*decimalDigits.erase(decimalDigits.begin()));
        exponent--;
    }
    std::string exponentStr = std::bitset<8>(exponent+127).to_string();
    //Calculate mantissa
    std::string mantissa;
    for (int i = static_cast<int>(wholeDigits.size()-1); i>=0; i --){
        if ((exponent > 0 && i == exponent) || (exponent < 0 && i == 0)){
            continue;
        }
        mantissa += convertChar(wholeDigits[static_cast<unsigned >(i)]);
    }
    for (const auto& i: decimalDigits){
        mantissa += convertChar(i);
    }
    unsigned trailing_0 = 23 - mantissa.size();
    for (unsigned  i = 0; i < trailing_0; ++ i){
        mantissa += '0';
    }
    std::string ans = (negative) ? "1" : "0";
    ans +=exponentStr;ans += mantissa;
    return ans;
}
unsigned int Converter::findLargestBit(int numIn){
    int i = 0;
    int pow = 1;
    while (numIn > pow ){
        ++i;
        pow *= 2;
    }
    return (numIn == pow || numIn == 0) ? i: (i-1);
}

void Converter::toBin(unsigned numIn, std::vector<bit> &container) {
    unsigned pow = 2u << (container.size()-1);
    int i = container.size();
    while (numIn != 0 &&  i >= 0){
        if (numIn >= pow){
            container[i] = bit::ONE;
            numIn -=pow;
        } else {
            container[i] = bit::ZERO;
        }
        --i;
        pow = pow >> 1u;
    }
}

void Converter::toBin(double decimal, std::vector<bit> &container) {
    int i = -1;
    double pow = 0.5;
    while (decimal != 0){
        if (decimal >= pow){
            container.emplace_back(bit::ONE);
            decimal -= pow;
        } else{
            container.emplace_back(bit::ZERO);
        }
        --i;
        pow /= 2;
    }
}

char Converter::convertChar(const Converter::bit &a) {
    if (a == bit::ONE){
        return '1';
    } else {
        return '0';
    }
}

double Converter::toFloat(const std::string &rep) {
    int neg = (rep[0] == '1')? -1 : 1;
    int exponent = static_cast<int>(binStrToNum(rep.substr(1, 8))) -127;
    double power = pow(2.0, exponent);
    double mantissa = mantissaToNum(rep.substr(9, 23));
    double result = neg* (1 + mantissa)*power;
    return result;
}


double Converter::mantissaToNum(const std::string &in) {
    double sum =0;
    double pow = 0.5;
    for (char i : in){
        sum +=((i == '0')? 0 : 1) * pow;
        pow /=2;
    }
    return sum;
}

double Converter::binStrToNum(const std::string &in) {
    double sum =0;
    double pow = 1u << (in.size()-1);
    for (char i : in){
        sum +=((i == '0')? 0 : 1) * pow;
        pow /=2;
    }
    return sum;
}

