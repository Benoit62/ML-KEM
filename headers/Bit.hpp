#pragma once

#ifndef BIT_HPP
#define BIT_HPP

class Bit {
    private:
        bool bit;
    public:
        void reverse();
        bool get();
        Bit(bool bit);
        ~Bit();
};

#endif