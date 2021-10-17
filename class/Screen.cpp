# include <string>

using namespace std;

// 每个类都会定义它自己的作用域，一个类就是一个作用域
class Screen
{
public:
    typedef string::size_type pos;// typedef 定义类型的别名
    // 告知编译器为我们合成默认的构造函数
    Screen() == default;
    Screen(pos ht, pos wt, char c):height(ht),width(wt),contents(ht*wd,c){}

    char get() const
    {
        return contents[cursor]
    }

    inline char get(pos ht, pos wt) const;
    
    Screen &move(pos r, pos c);

private:// 使用类型别名等价的声明一个类型的名字
    pos cursor = 0;
    pos height = 0, width = 0;
    string contents;
}