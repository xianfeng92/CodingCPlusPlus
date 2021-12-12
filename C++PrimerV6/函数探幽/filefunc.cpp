// filefunc.cpp

#include<iostream>
#include<fstream>
#include<cstdlib>

void file_it(ostream& os,double fo,const double fe[],int n);
const int LIMIT = 5;

int main()
{
    ofstream fout;
    const char* fn = "ep_data.txt";
    fout.open(fn);
    if(!fout.is_open())
    {
        cout << "Can't open file " << fn << '\n';
        exit(EXIT_FAILURE);
    }
    double objective;
    cout << "Enter the focal length your telescope objective in mm: ";
    cin >> objective;
    double eps[LIMIT];
    cout << "Enter the focal lengths, in mm , of " << LIMIT << " eyepieces: \n";
    for(int i = 0; i < LIMIT; i++)
    {
        cout <<"Eyepieces #" << i+1 <<'\n';
        cin >> eps[i];
    }
    file_it(fout,objective,eps,LIMIT);
    file_it(cout,objective,eps,LIMIT);
    cout << "Done!\n";
    return 0;
}

void file_it(ostream &os,double f0,const double fe[], int n)
{
    ios_base::fmtflags initial;
    initial = os.setf(ios_base::fixed);// save initial foemat state
    os.precision(0);
    os << "Focal length of objective: " << fo << " mm" << '\n';
    os.setf(ios_base::showpoint);
    os.precision(1);
    os.width(12);
    os << "f.1. eyepieces";
    os.width(15);
    os << "magnification" << endl;
    for(int i=0; i< n ; ++i)
    {
        os.width(12);
        os << fe[i];
        os.width(15);
        os << int (fo/fe[i] + 0.5);
    }
    os.setf(initial);
}


