#ifndef A50AB9BA_8CC9_447B_A265_0645ED1C9FB3
#define A50AB9BA_8CC9_447B_A265_0645ED1C9FB3

class Trace
{
public:
    Trace(const char* name)
    {
        if(traceIsActive)
        {
            cout << "Enter function " <<  name << endl;
            theFunctionName = new string(name);
        }
    }
    ~Trace();
    void debug(const string &msg);
    static bool traceIsActive;
private:
    char *theFunctionName;
};

#endif /* A50AB9BA_8CC9_447B_A265_0645ED1C9FB3 */
