#ifndef ADC2C2FB_4806_4E01_9BAA_FE2E384944F4
#define ADC2C2FB_4806_4E01_9BAA_FE2E384944F4

class BS
{
private:
    int q;
    double w;
public:
    BS():q(0), w(0){}
    BS(int k):q(k), w(0){}
    BS(double x):q(0),w(x){}
    BS(int k, double x):q(k),w(x){}
    void show() const {std::cout << q << ", " << w << '\n';}
};


class DR: public BS
{
private:
    short j;
public:
    using BS::BS;
    DR():j(-100){}
    DR(double x):BS(2*x),j(int(x)){}
    DR(int i):j(-2),BS(i, 0.5 * i){}
    void show() const {std::cout << j << ", "; BS.show();}

};


int main()
{
    DR o1;// using DR();
    DR o2(18.76);// use DR(double x)
    DR o3(10,1.8);// use BS(int, double)
    ...
}



#endif /* ADC2C2FB_4806_4E01_9BAA_FE2E384944F4 */
