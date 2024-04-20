#include "../headers/NTTmatrice.hpp"

NTTmatrice::NTTmatrice() {}  // Constructor
NTTmatrice::~NTTmatrice() {} // Destructor

std::vector<NTT> NTTmatrice::getRow(int i)
{
    return matrice[i];
}

// setter valeur i,j
void NTTmatrice::set(int i, int j, NTT value)
{
    // On vérifie si i est inférieur à la taille de la matrice
    // Si inférieur, on le met à l'index sinon on push_back
    // Puis de même avec j dans le vector à l'index i
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
        std::vector<NTT> v;
        v.push_back(value);
        matrice.push_back(v);
    }
}

// getter valeur i,j
NTT NTTmatrice::get(int i, int j)
{
    return matrice[i][j];
}

size_t NTTmatrice::sizeRow()
{
    return matrice.size();
}

size_t NTTmatrice::sizeCol()
{
    return matrice[0].size();
}

// surchage de l'addition de 2 matrices
NTTmatrice NTTmatrice::operator+(NTTmatrice &m)
{
    NTTmatrice res;
    for (int i = 0; i < matrice.size(); i++)
    {
        for (int j = 0; j < matrice[i].size(); j++)
        {
            res.set(i, j, matrice[i][j] + m.get(i, j));
        }
    }
    return res;
}

// surchage de la multiplication de 2 matrices
// A tester
NTTmatrice NTTmatrice::operator*(NTTmatrice &m)
{
    if (matrice[0].size() != m.sizeRow())
    {
        std::cout << "Multiplication impossible" << std::endl;
        return *this;
    }

    NTTmatrice res;
    for (int i = 0; i < matrice.size(); i++) // On parcourt les lignes de la matrice
    {
        for (int j = 0; j < matrice[i].size(); j++) // On parcourt les colonnes de la matrice
        {
            NTT sum;
            for (int k = 0; k < matrice[i].size(); k++) //
            {
                std::cout << "m1( " << i << " , " << k << " ) * m2( " << k << " , " << j << " )" << std::endl;
                sum = sum + matrice[i][k] * m.get(k, j);
            }
            std::cout << "res( " << i << " , " << j << " )" << std::endl;
            res.set(i, j, sum);
        }
    }
    return res;
}
