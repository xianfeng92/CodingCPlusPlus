#ifndef BIG_INT
#define BIG_INT

class BigInt
{
public:
    BigInt(const char *c);
    BigInt(unsigned = 0);
    BigInt(const BigInt &);
    ~BigInt();
private:
    char *digits;
    unsigned ndigits;
    unsigned size;
};

BigInt::BigInt(unsigned u)
{
    unsigned v = u;
    for(ndigits = 1;(v/=10) > 0; ++ndigits)
    {

    }
    digits = new char[size = ndigits];

    for(unsigned i = 0; i < ndigits; ++i)
    {
        digits[i] = u % 10;
        u /= 10;
    }
}

BigInt::BigInt(const BigInt &copyFrom)
{
    size = ndigits = copyFrom.ndigits;
    digits = new char[size];

    for(unsigned i = 0; i < ndigits; ++i)
    {
        digits[i] = copyFrom.digits[i];
    }
}

BigInt::~BigInt()
{
    delete[] digits;
}

#endif // BIG_INT
