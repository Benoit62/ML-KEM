#include "Bit.hpp"

void Bit::reverse(){
    // Reverse
    this->bit = !this->bit;
}

bool Bit::get(){
    return this->bit;
}

Bit::Bit(bool bit){
    this->bit = bit;
}

Bit::~Bit(){
    // Destructor
}