#include<iostream>
#ifndef D4E611A8_CDD4_4BD0_BF66_0CCC4ECA3598
#define D4E611A8_CDD4_4BD0_BF66_0CCC4ECA3598
class StringBad
{
private:
    char *str;// pointer to string
    int len;
    static int num_strings;// number of object
public:
    StringBad();
    StringBad(const char * str);
    ~StringBad();
    friend std::ostream & operator<<(std::ostream & os, const StringBad & st);
};

#endif /* D4E611A8_CDD4_4BD0_BF66_0CCC4ECA3598 */
