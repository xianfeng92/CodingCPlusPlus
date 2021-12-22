#ifndef C0B90B36_16E9_4F12_9009_2C8517AFEA67
#define C0B90B36_16E9_4F12_9009_2C8517AFEA67

typedef unsigned long Item;

class Stack
{
private:
    enum {MAX = 10};
    Item items[MAX];
    int top;
public:
    Stack();
    bool isEmpty() const;
    bool isFull() const;
    bool push(const Item& item);
    bool pop(Item& item);// pop top into items
};

#endif /* C0B90B36_16E9_4F12_9009_2C8517AFEA67 */
