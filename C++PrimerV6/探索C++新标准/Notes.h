#ifndef B323BD72_50BE_472D_B615_EA0753E70E77
#define B323BD72_50BE_472D_B615_EA0753E70E77

class Notes
{
private:
    int k;
    double x;
    std::string st;
public:
    Notes();
    Notes(int);
    Notes(int,double);
    Notes(int,double,std::string);
};

Notes::Notes(int kk,double xx, std::string st):k(k),xx(xx),st(st)
{

}

Notes::Notes():Notes(0,0.01,"Ah")
{

}

Notes::Notes(int kk):NOtes(kk,0.01,"oh")
{

}

Notes::Notes(int kk, double x):NOtes(kk,x,"Uh")
{

}


#endif /* B323BD72_50BE_472D_B615_EA0753E70E77 */
