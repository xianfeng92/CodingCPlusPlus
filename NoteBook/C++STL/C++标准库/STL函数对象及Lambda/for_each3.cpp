#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class MeanValue{
private:
    long num;
    long sum;
public:
    MeanValue():num(0),sum(0) {}

    void operator(int elem){
        ++num;
        sum += elem;
    }

    double value(){
        return static_cast<double>(sum) / static_cast<double>(num);
    }
};

int main(int argc, char **argv){

    vector<int> coll = {0,1,2,3,4,5,6,7,8,9};
    MeanValue mean = for_each(coll.begin(), coll.end(),MeanValue());

    cout << mean.value() << endl;

    return 0;
}