#ifndef BCDA71E0_EE12_45DA_A931_41B2796B18FB
#define BCDA71E0_EE12_45DA_A931_41B2796B18FB

#include <string>
namespace pers{

    struct Person{
        std::string fname;
        std::string lname;
    };

    void getPerson(Person&);
    void showPerson(const Person&);
}

namespace debts{
    using namespace pers;
    struct Debt{
        Person name;
        double amount;
    };
    void getDebt(Debt&);
    void showDebt(const Debt &);
    double sumDebt(const Debt deb[],int n);
}

#endif /* BCDA71E0_EE12_45DA_A931_41B2796B18FB */
