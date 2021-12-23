#ifndef AC29C986_6FFB_4A0E_8901_EFB32B12C6BC
#define AC29C986_6FFB_4A0E_8901_EFB32B12C6BC

class Time
{
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int h, int m = 0);
    void addMinute(int m);
    void addHour(int h);
    void reset(int h = 0, int m = 0);
    Time operator+(const Time& t) const;
    void show() const;
};

#endif /* AC29C986_6FFB_4A0E_8901_EFB32B12C6BC */
