#ifndef AE388675_6700_46A3_989D_38D4BE1BA704
#define AE388675_6700_46A3_989D_38D4BE1BA704

#include <iostream>

class bad_hmean
{
    private:
        double v1;
        double v2;
    public:
        bad_hmean(int a = 0, int b = 0):v1(a),v2(b){}
        void mesg();
};

inline void bad_hmean::mesg()
{
    std::cout << "hmean("<< v1 << "," << v2 << "):"
    << "invalid arguments: a = -b\n";
}

class bad_gmean
{
    public:
     double v1;
     double v2;
     bad_gmean(int a = 0, int b = 0):v1(a),v2(b){}
     const char * mesg();
};

inline const char * bad_gmean::mesg()
{
    return "gmean arguments shoule be >= 0\n";
}


#endif /* AE388675_6700_46A3_989D_38D4BE1BA704 */
