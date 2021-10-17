#ifndef BASKET_H
#define BASKET_H

class Basket
{
public:
    void addItem(const std::shared_ptr<Quote> sale)
    {
        items.insert(sale);
    }

    double total_recipt(std::ostream &) const;

private:
    static bool compare(const Basket &lhs, const Basket &rhs)
    {
        return lhs->isbn() < rhs->isbn();
    }
    std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};

#endif //