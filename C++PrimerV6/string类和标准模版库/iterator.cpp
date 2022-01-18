
struct Node
{
    double item;
    Node *p_next;
};

class iterator
{
    Node *pr;

public:
    iterator(): pr(0){}
    iterator(Node *p): pr(p) {}
    double operator*(){return pr->item;}
    iterator operator++(int)
    {
        iterator tmp = *this;
        pr = pr->next;
        return tmp;
    }
    // ... 
    operator==()
    operator!=()
    
};