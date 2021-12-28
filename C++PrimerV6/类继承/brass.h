#ifndef E0360DBD_DD97_4EE2_9D11_7AB406B2FFA6
#define E0360DBD_DD97_4EE2_9D11_7AB406B2FFA6

#include<string>

class Brass
{
private:
    std::string fullName;
    long acctNum;
    double balance;
public:
    Brass(const std::string &s = "NullBody", long an = -1, double bal = 0.0);
    void Deposit(double amt);
    virtual void withDraw(double amt);
    double Balance() const {return balance;}
    virtual void ViewAcct() const;
    virtual ~Brass() {};
};

class BrassPlus : public Brass
{
private:
    double maxLoan;
    double rate;
    double ownsBank;
public:
    BrassPlus(const std::string &s = "NullBody", double an = -1, double bal = 0.0, double ml = 500, double r = 0.11125);
    BrassPlus(const Brass &ba, double ml = 500, double r = 0.11125);
    virtual void ViewAcct() const;
    virtual void withDraw(double amt);
    void ResetMax(double m){ maxLoan = m;}
    void ResetRate(double m){ rate = m;}
    void resetOwns() { ownsBank = 0;}
};

#endif /* E0360DBD_DD97_4EE2_9D11_7AB406B2FFA6 */
