#ifndef BB9DAD87_FFA5_4280_9852_334066D4BE00
#define BB9DAD87_FFA5_4280_9852_334066D4BE00

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
    Time operator+(const Time& t);
    Time operator-(const Time& t);
    Time operator*(double d) const;
    friend Time operator*(double d, const Time& t){return t*d;};
    friend ostream& operator<<(ostream& os, const Time& t);
    void reset(int h = 0, int m = 0);
    Time operator+(const Time& t) const;
    void show() const;
};

#endif /* BB9DAD87_FFA5_4280_9852_334066D4BE00 */