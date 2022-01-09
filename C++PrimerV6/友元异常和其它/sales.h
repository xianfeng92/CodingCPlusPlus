#ifndef B668A86D_E02F_489A_A7E8_8666633077E8
#define B668A86D_E02F_489A_A7E8_8666633077E8

#include <stdexcept>
#include <string>

class Sales
{
    protected:
        enum {MONTHS = 12};

    public:
        class bad_index: public std::logic_error
        {
            private:
                int bi;
            public:
                explicit bad_index(int ix, const std::string &s = "Index Error in Sales Object");
                int bi_val() const { return bi;}
                virtual ~bad_index() throw(){}
        };
        explicit Sales(int yy = 0);
        Sales(int yy, const double *gr, int n);
        virtual ~Sales();
        int year() const { return year;}
        virtual double operator()(int i) const;
        virtual double &operator()(int i);
    private:
        double ggross[MONTHS];
        int year;
};

class LabeledSales: public Sales
{
    public:
        class nbad_index: public Sales::bad_index
        {
            private:
                std::string lbl;
            public:
                nbad_index(const std::string &lb, int ix, const std::string &s = "Index Error in LabeledSales Object\n");
                const std::string & label_val() const{return lbl;}
                virtual ~nbad_index() throw() {}
        };
        explicit LabeledSales(const std::string &lb = "none", int yy = 0);
        LabeledSales(connst std::strchr &lb,int yy, const double * gr, int n);
        virtual ~LabeledSales(){}
        const std::string & Label() const{return label;}
        virtual double operator()(int i)const;
        virtual double &operator()(int i);
    private:
        int label;
};

#endif /* B668A86D_E02F_489A_A7E8_8666633077E8 */
