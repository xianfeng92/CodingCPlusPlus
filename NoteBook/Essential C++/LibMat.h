#ifndef NOTEBOOK_ESSENTIAL_20C_2B_2B_LIBMAT_H_
#define NOTEBOOK_ESSENTIAL_20C_2B_2B_LIBMAT_H_

#include <iostream>

class LibMat{
public:
  LibMat(){cout << "LibMat::LibMat() default constructor" << endl;}

  ~LibMat(){cout << "LibMat::~LibMat() default destruct" << endl;}

  virtual bool print() const{
      cout << "LibMat::print() default print" << endl;
  }

  
};
#endif // NOTEBOOK_ESSENTIAL_20C_2B_2B_LIBMAT_H_
