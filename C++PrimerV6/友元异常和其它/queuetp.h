#ifndef FA4AB911_9F46_41B5_BDEF_928DC1BEB194
#define FA4AB911_9F46_41B5_BDEF_928DC1BEB194

template <typename Item>
class QueueTP
{
    private:
        enum {Q_SIZE = 10};
        class Node
        {
            public:
                Item item;
                Node *next;
                Node(const Item &i):item(i),next(0) {}
        };
        Node *front;
        Node *rear;
        int items;
        const int qsize;
        QueueTP(const QueueTP &q):qsize(0) {}
        QueueTP & operator=(const QueueTP &q){return *this;}
    public:
        QueueTP(int qs = Q_SIZE);
        ~QueueTP();
        bool isEmpty() const
        {
            return items == 0;
        }
        
        bool isFull() const
        {
            return qsize == Q_SIZE;
        }

        int queueCount() const
        {
            return qsize;
        }

        bool enqueue(const Item & item);
        bool dequeue(Item &item);

};

template <typename Item>
QueueTP<Item>::QueueTP(int qs):qsize(qs)
{
    front = rear = nullptr;
    items = 0;
}

template <typename Item>
QueueTP<Item>::~QueueTP()
{
    Node *temp;
    while(front != 0)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}

template <typename Item>
bool QueueTP<Item>::enqueue(const Item & item)
{
    if(isFull()) return false;
    Node *add = new Node(item);
    items++;
    if(front == 0)
    {
        front = add;
    }
    else
    {
        rear->next = add;
    }
    rear = add;
    return true;
}


bool QueueTP<Item>::dequeue(Item &item)
{
    if(front == 0)
    {
        return false;
    }
    item = front->item;
    items--;
    Node *temp = front;
    front = front->next;
    delete temp;
    if(items == 0)
    {
        rear = 0
    }
    return true;
}


#endif /* FA4AB911_9F46_41B5_BDEF_928DC1BEB194 */
