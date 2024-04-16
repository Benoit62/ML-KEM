#include <iostream>
#include <cstdint>

class Byte {
    private:
        uint8_t byte;
    public:
        Byte(uint8_t byte);
        ~Byte();
        uint8_t get();
        void set(uint8_t byte);
};

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