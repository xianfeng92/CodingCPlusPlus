#ifndef B8ABE663_8DF0_40E5_A95F_9E544BFDB37B
#define B8ABE663_8DF0_40E5_A95F_9E544BFDB37B

class SameClass
{
public:
    Someclass(SameClass &&f);
    SameClass() = default;
    SameClass(const SameClass &other) = default;
    SameClass &operator=(const SameClass &other) = default;
    ...
};

#endif /* B8ABE663_8DF0_40E5_A95F_9E544BFDB37B */
