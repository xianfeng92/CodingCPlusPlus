#include <iostream>
#include "studentc.h"

using std::cin;
using std::cout;
using std::endl;


void set(Student &sa,int n);
const int pupils = 3;
const int quizzes = 5;

int main()
{
    Student ada[pupils] = {Student(quizzes),Student(quizzes),Student(quizzes)};

    int i;
    for(i = 0; i < pupils; i++)
    {
        set(ada[i],quizzes);
    }
    cout << "Student List : " << endl;
    for(i = 0; i < pupils; i++)
    {
        cout << ada[i].Name() << endl;
    }
    cout << "Result : " << endl;
    for(i = 0; i < pupils; i++)
    {
        cout << endl << ada[i];
        cout << "average " << ada[i].Average() << endl;
    }
    cout << "Done";
    return 0;
}

void set(Student &sa, int n)
{
    cout << "Please Enter the student name:\n";
    getline(cin,sa.name);
    cout << "Please Enter " << n << "quiz socres";
    for(i = 0; i < quizzes; i++)
    {
        cin >> sa[i];
    }
    while(cin.get() != '\n')
    {
        continue;
    }
}