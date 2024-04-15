class Bit {
    private:
        bool bit;
    public:
        void reverse();
        Bit(bool bit);
        ~Bit();
};

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