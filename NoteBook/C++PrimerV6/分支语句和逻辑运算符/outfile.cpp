// outfile.cpp

#include<iostream>
#include<fstream>// for file I/O

int main()
{
    using namespace std;
    char automobile[50];
    int year;
    double a_price;
    double d_price;

    ofstream outfile;
    outfile.open("hello.txt");
    cout << "Enter to make and model of automobile: ";
    cin.getline(automobile,50);
    cout << "Enter the model of year: ";
    cin >> year;
    cout << "Enter the origin asking price: ";
    cin >> a_price;
    d_price = a_price * 0.913;

    // display information on screen with cout
    cout << fixed;
    cout.precision(2);
    cout.setf(ios_base::showpoint);
    cout << "Make and model " << automobile << endl;
    cout << "year " << year << endl;
    cout << " was asking " << a_price << endl;
    cout << "Now asking " << d_price << endl;

    // now do exact same thing using outFile instead of cout
    outFile.fixed;
    outFile.precision(2);
    outFile.self(ios_base::showpoint);
    outFile << "Make and model " << automobile << endl;
    outFile << "year " << year << endl;
    outFile << "was asking " << a_price << endl;
    outFile << "Now asking " << d_price << endl;
    return 0;
}

