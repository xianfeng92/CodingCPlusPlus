#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H

// 派生类可以访问基类的公有成员和受保护的成员（public and private）
class Bulk_Quote : public Quote
{
public:
    Bulk_Quote() = default;
    Bulk_Quote(const std::string &, double, std::size_t, double);
    double netPrice(std::size_t) const override;

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
}

#endif //