#include<iostream>
#include<string>

template<typename T1, typename T2>
class Pair
{
    private:
        T1 a;
        T2 b;
    public:
        T1 & first();
        T2 & second();
        T1 first() const;
        T2 second() const;
        Pair(const T1 &aval, const T2 &bval):a(aval), b(bval){}
        Pair(){}
};


template<typename T1, typename T2>
T1 & Pair<T1, T2>::first()
{
    return a;
}

template<typename T1, typename T2>
T2 & Pair<T1, T2>::second()
{
    return b;
}

template<typename T1, typename T2>
T1 Pair<T1, T2>::first() const
{
    return a;
}

template<typename T1, typename T2>
T2 Pair<T1, T2>::second() const
{
    return b;
}


int main()
{
    using std::cout;
    using std::endl;
    using std::string;

    Pair<string,int> ratings[4] = 
    {
        Pair<string,int>("NIO",1);
        Pair<string,int>("Apple",2);
        Pair<string,int>("XP",3);
        Pair<string,int>("BABA",4);
    };

    int joints = sizeof(ratings)/sizeof(Pair<string,int>);
    cout << "Rating：\t Eatery \n";
    for(int i = 0; i < joints; i++)
    {
        cout << ratings[i].second() << ":\t" << ratings[i].first() << endl;
    }
    cout << "Oops! Revise rating\n";
    ratings[3].first() = "NIONIO";
    ratings[3].second() = 6;
    cout << ratings[3].first() << ":\t" << ratings[3].second() << endl;
    return 0;
}