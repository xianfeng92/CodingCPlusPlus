#ifndef SUPERSTRING_H_
#define SUPERSTRING_H_

class SuperString {
 public:
  SuperString(const char* s = 0);
  SuperString(const SuperString& s);
  SuperString& operator=(const SuperString& s);

  ~SuperString() { delete[] str; }

 private:
  char* str;
};

inline SuperString::SuperString(const char *s):str(s)
{
    if(s != 0)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
}

inline SuperString::SuperString(const string &s):str(0)
{
    if(s.str)
    {
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);
    }
}

SuperString& SuperString::operator=(const SuperString &s)
{
    if(str != s.str)
    {
        delete[] str;
        str =  new char[strlen(s.str) + 1];
        strcpy(str, s.str);

    }
    else
    {
        str = 0;
    }
    return *this;
}

#endif  // SUPERSTRING_H_
