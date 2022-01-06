#include "studenti.h"

using std::string;
using std::ostream;
using std::endl;
using std::istream;

double Student::Average() const
{
    if(ArrayDb.size() > 0)
    {
        return ArrayDb.sum() / ArrayDb.size();
    }
    else
    {
        return 0;
    }
}


const string & Student::Name() const
{
    return (const string &)*this;
}

double & Student::operator[](int i)
{
    return ArrayDb::operator[](i);// using ArrayDb::operator[]()
}

double Student::operator[](int i) const
{
    return ArrayDb::operator[](i);
}


ostream &Student::arr_out(ostream &os) const
{
    int i;
    int lim = ArrayDb.size();

    if(lim > 0)
    {
        for(i=0;i<lim;i++)
        {
            os << ArrayDb::operator[](i) << " ";
            if(i % 5 == 4)
            {
                os << endl;
            }

        }
        if(i % 5 != 0)
        {
            os << endl;
        }
    }
    else
    {
        os << "empty array" << endl;
    }
    return os;
}


istream & operator>>(istream & is, Student &st)
{
    is >> (string &)st << endl;
    return is;
}

istream & get(istream & is, Student &st)
{
    getline(is, (string &)st);
    return is;
}


ostream & operator << (ostream & os, const Student &st)
{
    os << (const string &)st << endl;
    st.arr_out(os);
    return os;
}











