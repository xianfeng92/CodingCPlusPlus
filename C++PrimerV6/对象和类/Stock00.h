#ifndef E14C33FD_BE4B_4C8A_BC23_01FEB92F5BA4
#define E14C33FD_BE4B_4C8A_BC23_01FEB92F5BA4

#include<string>

class Stock
{
private:
    long share;
    double share_val;
    double total_val;
    void set_tot() { total_val - share_val *share; }

public:
    void acquire(const std::string &co, long n, double pr);
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};

#endif /* E14C33FD_BE4B_4C8A_BC23_01FEB92F5BA4 */
