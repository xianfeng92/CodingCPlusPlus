#ifndef B38BB383_C6A4_406F_92A3_88E37B4C7E00
#define B38BB383_C6A4_406F_92A3_88E37B4C7E00

// Abstract base Class
class AcctABC
{
private:
    std::string fullName;
    long acctNum;
    double balance;

protected:
    struct Formating
    {
        std::ios_base::fmtflags flag;
        std::streamsize pr;
    };
    const std::string &fullName() const { return fullName; }
    long acctNum() const { return acctNum; }
    Formating setFormat() const;
    void restore(Formating &f) const;

public:
    AcctABC(const std::string &s = "NullBody", long an = -1, double bal = 0.0);
    void Deposit(double amt);
    virtual void Withdraw(double amt) = 0; // pure virtual function
    double Balance() const { return balance; }
    virtual void ViewAcct() const = 0; // pure virtual function
    virtual ~AcctABC() {}
};

// Brass Account class
class Brass : public AcctABC
{
public:
    Brass(const std::string &s = "NullBody", long an = -1, double bal = 0.0) : AcctABC(s, an, bal) {}
    virtual void Withdraw()(double amt);
    virtual void ViewAcct() const;
    virtual ~Brass(){};
};

//Brass Plus Account class
class BrassPlus : public AcctABC
{
private:
    double maxLoan;
    double rate;
    double ownsBank;

public:
    BrassPlus(const std::string &s = "NullBody", long an = -1, double bal = 0.0, double ml = 500, double r = 0.10);
    BrassPlus(const Brass &ba, double ml = 500, double r = 0.1);
    virtual void ViewAcct() const;
    virtual void withDraw(double amt);
    void ResetMax(int m) { maxLoan = m; }
    void ResetRate(int r) { rate = r; }
    void ResetOwns(iny n) { ownsBank = n; }
};

#endif /* B38BB383_C6A4_406F_92A3_88E37B4C7E00 */
