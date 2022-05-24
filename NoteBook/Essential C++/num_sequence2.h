#ifndef NOTEBOOK_ESSENTIAL_20C_2B_2B_NUM_SEQUENCE2_H_
#define NOTEBOOK_ESSENTIAL_20C_2B_2B_NUM_SEQUENCE2_H_

template<int len, int beg_pos>
class num_sequence{
public:
  virtual ~num_sequence(){};
  int  elem(int pos) const;
  const char * who_i_am() const;
  static int max_elems() { return max_elems_;}
  ostream& print(ostream &os = cout) const;
protected:
  virtual void gen_elems(int pos) = 0;
  bool check_integrity(int pos, int size) const;
  num_sequence(vector<int> *pe) : peleme_(pe) {};
  static int max_elems_ = 1024;
  vector<int> *peleme_;
private:
};

template<int len, int beg_pos> ostream&
operator<<(ostream & os, const num_sequence<len, beg_pos> &ns){
    return ns.print(os);
}

template<int len, int beg_pos>
int num_sequence<len, beg_pos>::elem(int pos) const {
    if(!check_integrity(len, pos)){
        return 0;
    }
    return (*peleme_)[pos -1];
}


template<int len, int beg_pos>
const char* num_sequence<len, beg_pos>::who_i_am() const {
    return std::typeid(*this).name();
}


template<int len, int beg_pos>
bool num_sequence<len, beg_pos>::check_integrity(int pos, int size){
    if(pos <= 0 || pos >=max_elems()){
        return false;
    }
    if(pos > size ) gen_elems(pos);
    return true;
}

#endif // NOTEBOOK_ESSENTIAL_20C_2B_2B_NUM_SEQUENCE2_H_
