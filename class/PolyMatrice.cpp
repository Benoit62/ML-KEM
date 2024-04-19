#include "../headers/PolyMatrice.hpp"

PolyMatrice::PolyMatrice() {}  // Constructor
PolyMatrice::~PolyMatrice() {} // Destructor

void PolyMatrice::set(int i, int j, Poly value)
{
    if (i < matrice.size())
    {
        if (j < matrice[i].size())
        {
            matrice[i][j] = value;
        }
        else
        {
            matrice[i].push_back(value);
        }
    }
    else
    {
        std::vector<Poly> v;
        v.push_back(value);
        matrice.push_back(v);
    }
}

// getter valeur i,j
Poly PolyMatrice::get(int i, int j)
{
    return matrice[i][j];
}

size_t PolyMatrice::sizeRow()
{
    return matrice.size();
}

size_t PolyMatrice::sizeColumn()
{
    return matrice[0].size();
}

PolyMatrice PolyMatrice::operator+(PolyMatrice &m)
{
    PolyMatrice res;
    for (int i = 0; i < matrice.size(); i++)
    {
        for (int j = 0; j < matrice[i].size(); j++)
        {
            res.set(i, j, matrice[i][j] + m.get(i, j));
        }
    }
    return res;
}
