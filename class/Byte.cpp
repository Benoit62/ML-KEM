#include <iostream>

#ifndef BYTE_H
#define BYTE_H

class Byte {
    private:
        uint8_t byte;
    public:
        Byte(uint8_t byte){
            this->byte = byte;
        }
        ~Byte(){
            // Destructor
        }
        uint8_t get(){
            return this->byte;
        }
        void set(uint8_t byte){
            this->byte = byte;
        }
};

#endif // BYTE_H