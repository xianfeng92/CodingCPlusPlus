#ifndef ACDD3504_2655_488D_8CFC_C5195EC6E1C2
#define ACDD3504_2655_488D_8CFC_C5195EC6E1C2
template <typename Type>
class Stack
{
    private:
        enum {MAX = 10};
        Type item[MAX];
        int top;
    public:
        Stack();
        bool isEmpty() const;
        bool isFull() const;
        bool push(const Type & value);
        bool pop(Type & value);
};

template <typename Type>
Stack<Type>::Stack()
{
    top = 0;
}

template <typename Type>
bool Stack<Type>::isEmpty() const
{
    return top == 0;
}

template <typename Type>
bool Stack<Type>::isFull() const
{
    return top == MAX;
}

template <typename Type>
bool Stack<Type>::push(const Type & value)
{
    if(top < MAX)
    {
        items[top++] = value;
        return true;
    }
    return false;
}

template <typename Type>
bool Stack<Type>::pop(Type & item)
{
    if(top > 0)
    {
        item = items[--top];
        return true;
    }
    return false;
}

#endif /* ACDD3504_2655_488D_8CFC_C5195EC6E1C2 */