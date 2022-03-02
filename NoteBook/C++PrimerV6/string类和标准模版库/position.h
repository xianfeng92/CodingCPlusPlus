#ifndef B18834E3_5536_4B67_8898_500B7914710D
#define B18834E3_5536_4B67_8898_500B7914710D

class Position
{
private:
    int x;
    int y;
    int z;
public:
    Position(int x, int y, int z)::x(x), y(y), z(z){ }
    ...
    // no initializer_list constructor
};

#endif /* B18834E3_5536_4B67_8898_500B7914710D */
