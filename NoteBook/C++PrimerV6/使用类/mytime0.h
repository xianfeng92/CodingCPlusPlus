#ifndef A3278E75_2B07_4E7F_B108_C15F9D0C188E
#define A3278E75_2B07_4E7F_B108_C15F9D0C188E

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
    Time sum(const Time& t) const;
    void show() const;
};

#endif /* A3278E75_2B07_4E7F_B108_C15F9D0C188E */
