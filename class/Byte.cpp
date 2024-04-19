#include "../headers/Byte.hpp"

Byte::Byte(uint8_t byte){
    this->byte = byte;
}

Byte::~Byte(){
    // Destructor
}

uint8_t Byte::get(){
    return this->byte;
}

void Byte::set(uint8_t byte){
    this->byte = byte;
}