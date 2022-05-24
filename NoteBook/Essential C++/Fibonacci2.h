#ifndef NOTEBOOK_ESSENTIAL_20C_2B_2B_FIBONACCI2_H_
#define NOTEBOOK_ESSENTIAL_20C_2B_2B_FIBONACCI2_H_

#include "num_sequence2.h"

template <int length, int beg_pos = 1>
class Fibonacci : public num_sequence<length, beg_pos>{
public:
  Fibonacci(): num_sequence<length, beg_pos>(&elems_){}
protected:
  virtual void gen_elems(int pos) const;
  static vector<int> elems_;
};


template<int length, int beg_pos>
vector<int> Fibonacci<length, beg_pos>::elems_;

template<int length, int beg_pos>
void Fibonacci<length, beg_pos>::gen_elems(int pos) const{
    if(pos < 0 || pos >= max_elems()) return;
    if(elem_.empty()){
        elem_.push_back(1);
        elems_.push_back(2);
    }
    if(elem_.size() < pos){
        //...
    }
}

#endif // NOTEBOOK_ESSENTIAL_20C_2B_2B_FIBONACCI2_H_
