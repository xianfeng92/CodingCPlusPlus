#ifndef FDFCF7FE_05DB_4555_850F_8508F9E13F8D
#define FDFCF7FE_05DB_4555_850F_8508F9E13F8D

class Trace
{
public:
    Trace(const string &name);
    ~Trace();
    void debug(const string &msg);
    static bool traceIsActive;
private:
    string theFunctionName;
};

#endif /* FDFCF7FE_05DB_4555_850F_8508F9E13F8D */
