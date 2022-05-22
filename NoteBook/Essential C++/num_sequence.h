#ifndef NOTEBOOK_ESSENTIAL_20C_2B_2B_NUM_SEQUENCE_H_
#define NOTEBOOK_ESSENTIAL_20C_2B_2B_NUM_SEQUENCE_H_
#include <typeinfo>

class num_sequence{
public:
    virtual ~num_sequence(){};
    virtual const char* who_i_am() const{ return typeid(*this).name(); };
};

#endif // NOTEBOOK_ESSENTIAL_20C_2B_2B_NUM_SEQUENCE_H_
