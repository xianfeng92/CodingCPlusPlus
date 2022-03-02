#ifndef C7F17385_69DC_4314_B175_C7A53298D04E
#define C7F17385_69DC_4314_B175_C7A53298D04E

class Session
{
private:
    int mem1 = 10;
    double mem2{12321};
    short mem3;
public:
    Session();
    Session(short s):mem3(s) {}
    Session(int n, double d, short s):mem1(n), mem2(d), mem3(s){}
    ...
};


#endif /* C7F17385_69DC_4314_B175_C7A53298D04E */
