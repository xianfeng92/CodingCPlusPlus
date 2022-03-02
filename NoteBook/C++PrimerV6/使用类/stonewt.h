#ifndef AD456C3D_BBFF_4001_834D_691A99692B68
#define AD456C3D_BBFF_4001_834D_691A99692B68

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
    void show_lbs() const;
    void show_stone() const;
};

#endif /* AD456C3D_BBFF_4001_834D_691A99692B68 */
