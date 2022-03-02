// sumafile.cpp

#include<iostream>
#include<fstream>
#include<cstdlib>

const int SIZE = 60;

int main()
{
    using namespace std;
    char filename[SIZE];
    ifstream inFile;
    cout << "Enter name of data file: ";
    cin.getLine(filename,SIZE);
    inFile.open(filename);
    if(!inFile.is_open())
    {
        cout << "Can not open file " << filename << endl;
        cout << "program terminated" << endl;
        exit(EXIT_FAILURE);
    }
    double value;
    double sum = 0;
    int count = 0;
    
    inFile >> value;
    
    while(inFile.good())
    {
        ++count;
        sum += value;
        inFile >> value;
    }
    if(inFile.eof())
    {
        cout  << "End of file Reached" << endl;
    }
    else if(inFile.fail())
    {
        cout << "Input terminated by data mismatch.\n";
    }
    else
    {
        cout << "Input terminated by unknow reason.\n";
    }
    if(count == 0)
    {
        cout << "No data Processed.\n";
    }
    else
    {
        cout << "Item read : " << count << endl;
        cout << "sum : " << sum << endl;
        cout << "average : " << average << endl;
    }
    inFile.close();
    return 0;
}