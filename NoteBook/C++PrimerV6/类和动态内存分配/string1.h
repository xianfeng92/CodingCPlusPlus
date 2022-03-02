#ifndef A6AA84D4_2137_4DDD_9CE5_A2C0C53EC442
#define A6AA84D4_2137_4DDD_9CE5_A2C0C53EC442
#include<iostream>

using std::istream;
using std::ostream;

class String
{
    private:
        char * str;
        int len;
        static int num_strings;
        static const int CINLIM = 80;// cin input limit
    public:
        String(const char * str);
        String();
        String(const String &);
        ~String();
        int length() const {return len;}

        // overload operator method
        String operator=(const String &);
        String operator=(const char *);
        char &operator[](int i);
        const char &operator[](int i) const;

        // overload operator friends
        friend String operator<(const String &st, const String &st2);
        friend String operator>(const String &st1, const String &st2);
        friend String operator==(const String &st, const String &st2);
        friend ostream & operator<<(ostream & os, const String &str);
        friend istream & operator>>(ostream & os, String &str);

        // static function
        static int HowMany() const;
};

#endif /* A6AA84D4_2137_4DDD_9CE5_A2C0C53EC442 */
