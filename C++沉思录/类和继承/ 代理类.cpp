

假设有一个表示不同种类的交通工具的类派生层次：

class Vehicle
{
    virtual double weight() const = 0;
    virtual void start() = 0;
    //...
};



