#include<iostream>
#include<string>
#include "boost/lexical_cast.hpp"

int main()
{
    using namespace std;
    cout << "Enter your weight:\n";
    float weight;
    cin >> weight;

    string gain = "A 10% increase raises\n";

    string wt = boost::lexical_cast<string>(weight);
    gain = gain + wt + " to";
    weight = 1.1 * weight;
    gain = gain + boost::lexical_cast<float>(weight) + ". ";
    cout << gain << endl;
    return 0;
}