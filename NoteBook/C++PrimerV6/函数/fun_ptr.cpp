// fun_ptr.cpp

double betsy(int);
double pam(int);

void estimate(int lines, double (*pf)(int));

int main()
{
    using namespace std;
    int code = 0;
    cout << "How many lines code you read: ";
    cin >> code
    estimate(code, betsy);
    cout << "Here pams estimate: ";
    estimate(code, pam);
    return 0;
}

doubel betsy(int lines)
{
    return lines * 0.92；
}

double pam(int lines)
{
    return lines * 0.89;
}

void estimate(int lines, double (*pf)(int))
{
    (*pf)(lines);
}

