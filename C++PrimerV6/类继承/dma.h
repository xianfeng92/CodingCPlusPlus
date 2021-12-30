#ifndef D27F4FBA_5827_4041_B1C6_B67B028327C0
#define D27F4FBA_5827_4041_B1C6_B67B028327C0

// base class using DMA
class baseDMA
{
private:
    char * label;
    int rating;
public:
    baseDMA(char * l = "none", int r = 0);
    baseDMA(const baseDMA & other);
    virtual ~baseDMA();
    baseDMA & operator=(const baseDMA & other);
    friend std::ostream & operator<<(std::ostream &os, const baseDMA &rs);
};

class lacksDMA : public baseDMA
{
private:
    enum { COL_LEN = 40};
    char colors[COL_LEN];
public:
    lacksDMA(const char * c = "blank", const char * l = "null", int r = 0);
    lacksDMA(const char * c , const baseDMA & other);
    friend std::ostream & operator<<(std::ostream &os, const lacksDMA &rs);

};

class hasDMA : public baseDMA
{
private:
    char * style;
public:
    hasDMA(const char * s = "none", const char * l = "null", int r = 0);
    hasDMA(const char * s, const baseDMA & other);
    hasDMA(const hasDMA & other);
    ~hasDMA();
    hasDMA & operator=(const hasDMA & other);
    friend std::ostream & operator<<(std::ostream &os, const hasDMA &rs);

};

#endif /* D27F4FBA_5827_4041_B1C6_B67B028327C0 */
