#pragma once

#ifndef BYTE_HPP
#define BYTE_HPP

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

#endif