#ifndef A2178979_144D_44E6_93E6_A778A4BF6346
#define A2178979_144D_44E6_93E6_A778A4BF6346

class Linear
{
private:
    double slope;
    double y0;
public:
    Linear(double s1_ = 0, double y_ = 0):slope(s1_), y0(y_) {}
    double operator()(double x) {return x*slope + y0;}
};
#endif /* A2178979_144D_44E6_93E6_A778A4BF6346 */
