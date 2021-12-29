#ifndef B0010983_F900_46A5_8E62_ECC2C647F8E8
#define B0010983_F900_46A5_8E62_ECC2C647F8E8
#include "baseDMA.h"

class hasDMA : public baseDMA
{
private:
    char * style;// using new in constructor
public:
    hasDMA & operator = (const hasDMA &other);
    hasDMA(const hasDMA &other);
    ~hasDMA();
};

#endif /* B0010983_F900_46A5_8E62_ECC2C647F8E8 */
