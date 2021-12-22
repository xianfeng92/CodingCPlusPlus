#ifndef CAB47F49_65A5_461D_8B44_16C4476D2470
#define CAB47F49_65A5_461D_8B44_16C4476D2470

#include <string>
class Stock
{
    private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot(){total_val = share_val * shares;};

    public:
    Stock();// default constructor
    Stock(std::string &co, long n = 0, double pr = 0);
    ~Stock();// destructor
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};

#endif /* CAB47F49_65A5_461D_8B44_16C4476D2470 */
