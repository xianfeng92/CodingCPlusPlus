#ifndef QUOTE_H
#define QUOTE_H


class QUOTE
{
    public:
    Quote() = default;
    Quote(const string &book, double sales_price):bookNo(book),price(sales_price) {}

    // 派生类负责改写使用不同的折扣算法
    virtual double net_price(size_t n) const { return price * n; }
    // 基类通常会定义一个虚析构函数，即使该函数不执行任何实际操作也如此
    virtual ~Quote() = default;

    private:
    std::string bookNo;
    protected:
    double price = 0.0;
}

#endif