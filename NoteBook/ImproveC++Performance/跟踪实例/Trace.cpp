#include  "Trace.h"

inline Trace::Trace(const string &name):theFunctionName(name)
{
    if(traceIsActive)
    {
        cout << "Enter function " << name << endl;
    }
}


inline Trace::debug(const string &msg)
{
    if(traceIsActive)
    {
        cout << msg << endl;
    }
}

inline Trace::~Trace
{
    if(traceIsActive)
    {
        cout <<  "Exit function " << theFunctionName << endl;
    }
}


