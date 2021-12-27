#ifndef E3CB83B9_79C1_49A6_9578_6B7570EA6BD7
#define E3CB83B9_79C1_49A6_9578_6B7570EA6BD7

class Customer
{
private:
    long arrive;
    int processtime;

public:
    Customer(){arrive = processtime = 0;}
    void set(long when);
    long when() const {return arrive;}
    int ptime() const {return processtime;}
};

typedef Customer Item;

class Queue
{
    struct Node {Item item; struct Node *next; };
    enum {Q_SIZE = 10};
private:
    Node *front;
    Node *rear;
    int items;
    const int qsize;
    Queue(const Queue *q):qsize(0){}
    Queue & operator=(const Queue & q){ return *this; }
public:
    Queue(int qs = Q_SIZE);
    ~Queue();
    bool isEmpty() const;
    bool isFull() const;
    int queueCount() const;
    bool enqueue(const Item & item);
    bool dequeue(Item &item);
};
#endif /* E3CB83B9_79C1_49A6_9578_6B7570EA6BD7 */
