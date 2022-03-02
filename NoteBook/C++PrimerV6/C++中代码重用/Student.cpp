#include "studentc.h"

using std::ostream;
using std::endl;
using std::istream;
using std::string;


double Student::Average() const
{
    if(scores.size() > 0)
    {
        return scores.sum() / scores.size();
    }
    else
    {
        return 0;
    }
}


const string & Student::Name() const
{
    return name;
}

double & Student::operator[](int i)
{
    return scores[i];
}


double Student::operator[](int i) const
{
    return scores[i];
}


ostream & Student::arr_out(ostream &os) const
{
    int i;
    int lim = scores.size();
    if(lim > 0)
    {
        for(int i = 0; i < lim; i++)
        {
            os << scores[i] << " ";
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
        os << "Empty array";
    }
    return os;
}


istream & operator>>(istream & is, Student &st)
{
    is >> stu.name;
    return is;
}


istream & getline(istream & is, Student &st)
{
    getline(is, st.name);
    return is;
}


ostream & operator << (ostream & os, const String &st)
{
    os << "Scores for " << st.name << '\n';
    st.arr_out(os);
    return os;
}