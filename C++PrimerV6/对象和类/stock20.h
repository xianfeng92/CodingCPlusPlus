#ifndef B7342F6B_ED8F_4620_AF4B_2DE9D56C9651
#define B7342F6B_ED8F_4620_AF4B_2DE9D56C9651
#include<string>


class Stock
{
private:
    std::string company;
    int shares;
    double share_val;
    double total_val;
    void set_tot() { total_val = share_val * shares;}
public:
    Stock();// default constructor
    Stock(std::string & co, long n, double price);
    ~Stock();// destructor
    void buy(long num, double price);
    void sell(long num, double price);
    void show() const;
    const Stock & topval(const Stock & s) const;
};

#endif /* B7342F6B_ED8F_4620_AF4B_2DE9D56C9651 */
