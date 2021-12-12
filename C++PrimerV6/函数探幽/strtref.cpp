// strtref.cpp

#include <iostream>
#include <string>

struct free_throws
{
    std::string name;
    int made;
    int attempts;
    float percent;
};

void display(const free_throws &ft);
void set_pc(free_throws &ft);
free_throws &accumulate(free_throws &target, const free_throws & sources);

int main()
{
    // partital initializations --- remaining members set to 0
    free_throws one = {"hello",11,12};
    free_throws two = {"you",2,3};
    free_throws three = {"are",123,326};
    free_throws four = {"smart",23,32};
    free_throws five = {"too",12,21};
    free_throws team = {"xforg",12,989};

    // no initialization

    free_throws dup;

    set_pc(one);
    display(one);
    accumulate(team,one);
    display(team);

    // use return value as parameter
    display(accumulate(team,two));
    accumulate(accumulate(team,three),four);
    display(team);
    // using return as assign
    dup = accumulate(team,five);

    std::cout << "Display Team: ";
    display(team);
    std::cout << "Display dup after assignment: ";
    display(dup);
    set_pc(four);
    // ill advice assignment
    accumulate(team,five) = four;
    std::cout << "Display dup after ill advice assignment: ";
    display(dup);
    return 0;
}


void display(const free_throws &ft)
{
    using std::cout;
    cout << "Name: " << ft.name << '\n';
    cout << " Made by: " << ft.made << '\n';
    cout << "attempts: " << ft.attempts << '\n';
    cout << "Percent: " << ft.percent << '\n';
}


void set_pc(free_throws &ft)
{
    if(ft.attempts != 0)
    {
        ft.percent = 100.0f * float(ft.made)/float(ft.attempts);
    }
    else
    {
        ft.percent = 0;
    }
}


free_throws & accumulate(free_throws &target, const free_throws &sources)
{
    target.attempts += sources.attempts;
    target.made += sources.made;
    set_pc(target);
    return target;
}


