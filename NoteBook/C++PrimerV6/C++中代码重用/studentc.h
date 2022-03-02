#ifndef BD0FF45B_A11F_4C12_81E1_91EE1476D1F3
#define BD0FF45B_A11F_4C12_81E1_91EE1476D1F3
#include<iostream>
#include<string>
#include<valarray>

class Student
{
    private:
        typedef std::valarray<double> ArrayDb;
        std::string name;
        ArrayDb scores;
        std::ostream & arr_out(std::ostream &os) const;
    public:
        Student():name("Null Student"),scores(){}
        explicit Student(const std::string &s):name(s),scores(){}
        explicit Student(int n):name("Nully"),scores(n){}
        Student(const std::string &s, ArrayDb &a):name(s),scores(a){}
        Student(const char *str, const double *pd, int n):name(str),scores(pd,n){}
        ~Student(){}
        double Average() const;
        const std::string & Name() const;
        double operator[](int i) const;
        friend std::istream & operator>>(td::istream &is, Student &stu);
        friend std::istream & getline(std::istream &is, Student &stu);
        friend std::ostream & operator<<(std::ostream & os, const Student &stu);
};

#endif /* BD0FF45B_A11F_4C12_81E1_91EE1476D1F3 */
