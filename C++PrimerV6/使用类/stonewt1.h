#ifndef D9768AC8_F025_496B_BD96_4D8D5BF0E4EA
#define D9768AC8_F025_496B_BD96_4D8D5BF0E4EA

class Stonewt
{
private:
    enum{Lbs_per_stn = 14};
    int stone; 
    double psd_left;
    double pounds;
public:
    Stonewt(double lbs);
    Stonewt(int stn, double lbs);
    Stonewt();
    ~Stonewt();
    operator int() const;
    operator double() const;
    void show_lbs() const;
    void show_stone() const;
};

#endif /* D9768AC8_F025_496B_BD96_4D8D5BF0E4EA */
