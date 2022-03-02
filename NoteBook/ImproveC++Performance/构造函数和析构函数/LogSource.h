#ifndef LOGSOURCE_H_
#define LOGSOURCE_H_

class BaseLogSource
{
public:
    BaseLogSource(){}
    virtual ~BaseLogSource(){}
};

class LogSource : public BaseLogSource
{
public:
    LogSource(const char* name, int num):filename(name), linenum(num){}
    ~LogSource(){}
    char *file();
    int line();
private:
    char *filename;
    int linenum;
};

#endif // LOGSOURCE_H_
