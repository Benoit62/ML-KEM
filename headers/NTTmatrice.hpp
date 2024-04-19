#pragma once

#ifndef NTTMATRICE_HPP
#define NTTMATRICE_HPP

#include "../class/NTT.cpp"
#include <vector>
#include <iostream>

class NTTmatrice
{
private:
    std::vector<std::vector<NTT>> matrice;

public:
    NTTmatrice();
    ~NTTmatrice();
    std::vector<NTT> getRow(int i);
    void set(int i, int j, NTT value);
    NTT get(int i, int j);
    size_t sizeRow();
    size_t sizeCol();
    NTTmatrice operator+(NTTmatrice &m);
    NTTmatrice operator*(NTTmatrice &m);
};


#endif 