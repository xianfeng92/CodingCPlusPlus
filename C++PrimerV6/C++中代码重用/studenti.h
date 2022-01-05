#ifndef D183D539_F2C2_4EB9_BB25_53E9EF2F1F78
#define D183D539_F2C2_4EB9_BB25_53E9EF2F1F78

#include <iostream>
#include <string>
#include <valarray>

class Student::private std::string, private std::valarray<double>
{
    private:
        typedef std::valarray<double> ArrayDb;
        std::ostream& arr_out(std::ostream& os) const;
    public:
        Student()::std::string("Null Student"),ArrayDb(){}
        explicit Student(std::string &s)::std::string(s),ArrayDb(){}
        explicit Student(int n)::std::string("Nully"),ArrayDb(n){}
        Student(const std::string &s, int n)::std::string(s),ArrayDb(n){}
        Student(const std::string &s, const ArrayDb &ad)::std::string(s),ArrayDb(ad){}
        Student(const char *str,const double *db, int n)::std::string(str),ArrayDb(db,n){}
        ~Student(){}
        double Average() const;
        double &operator[](int i);
        double operator[](int i) const;
        const std::string & Name() const;

        friend istream & operator>>(istream & is, Student &st);
        friend istream & getline(istream & is, Student &st);
        friend ostream & operator<<(std::ostream &os, const Student &stu);
};

#endif /* D183D539_F2C2_4EB9_BB25_53E9EF2F1F78 */
