class Bit {
    private:
        bool bit;
    public:
        void reverse();
        bool get();
        Bit(bool bit);
        ~Bit();
};

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