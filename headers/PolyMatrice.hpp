#pragma once

#ifndef POLYMATRICE_HPP
#define POLYMATRICE_HPP

#include "../class/NTT.cpp"
#include <vector>
#include <iostream>

class PolyMatrice
{
private:
    std::vector<std::vector<Poly>> matrice;

public:
    PolyMatrice();
    ~PolyMatrice();
    void set(int i, int j, Poly value);
    Poly get(int i, int j);
    size_t sizeRow();
    size_t sizeColumn();
    PolyMatrice operator+(PolyMatrice &m);
};

#endif