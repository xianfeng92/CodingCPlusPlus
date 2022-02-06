#include  "Tracev3.h"


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
        delete theFunctionName;
    }
}