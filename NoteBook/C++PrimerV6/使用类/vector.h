#ifndef D2296DB4_9B7D_4F94_BE88_030482F5ED53
#define D2296DB4_9B7D_4F94_BE88_030482F5ED53
#include<iostream>

namespace VECTOR 
{
    class vector
    {
        public:
            enum Mode{RECT,POL};
        private:
            double x;
            double y;
            double mag;
            double ang;
            Mode mode;
            void set_mag();
            void set_ang();
            void set_x();
            void set_y();
        public:
            vector();
            vector(double x, double y, Mode mode = RECT);
            void vector(double x, double y, Mode mode = RECT);
            ~vector();
            double xval() const {return x;};
            double yval() const {return y;};
            double magval() const {return mag;};
            double angval() const {return ang;};
            void polar_mode();
            void rec_mode();
            vector operator+(const vector& b) const;
            vector operator-(const vector& b) const;
            vector operator-() const;
            vector operator*(double n) const;
            friend vector operator*(double n,const vector& b) const;
            friend std::ostream &operator<<(std::ostream &os,const vector& v) const;
    };
}// end namespace VECTOR

#endif /* D2296DB4_9B7D_4F94_BE88_030482F5ED53 */
