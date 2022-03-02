extern int shared;
int main() //全局符号
{
    int a = 100;
    swap(&a, &shared);
}