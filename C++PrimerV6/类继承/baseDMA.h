#ifndef A5FCE15F_3113_4BFB_99EE_B50278FB9BBC
#define A5FCE15F_3113_4BFB_99EE_B50278FB9BBC

class baseDMA
{
private:
    char * label;
    int rating;
public:
    baseDMA(char * l = "null", int r = 0);
    baseDMA(const baseDMA & other);
    virtual ~baseDMA();
    baseDMA & operator=(const baseDMA & other);
    ...
};

#endif /* A5FCE15F_3113_4BFB_99EE_B50278FB9BBC */
