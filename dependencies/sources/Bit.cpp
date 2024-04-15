#ifndef BIT_H
#define BIT_H

class Bit {
    private:
        bool bit;
    public:
        void reverse(){
            // Reverse
            this->bit = !this->bit;
        }
        Bit(bool bit){
            this->bit = bit;
        }
        ~Bit(){
            // Destructor
        }
        bool get(){
            return this->bit;
        }
};

#endif // BIT_H
