#include "../dependencies/headers/Bit.hpp"

void Bit::reverse(){
    // Reverse
    this->bit = !this->bit;
}

Bit::Bit(bool bit){
    this->bit = bit;
}

Bit::~Bit(){
    // Destructor
}
