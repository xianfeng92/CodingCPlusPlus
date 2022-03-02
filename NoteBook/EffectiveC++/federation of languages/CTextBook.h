#ifndef CTEXTBOOK_H_
#define CTEXTBOOK_H_

class CTextBook
{
public:
    ...
    char & operator[](std::size_t position) const// bitwise const 声明
    {
        return pText[position];
    }
private:
    char *pText;
    mutable std::size_t textLength;// 这些成员变量可能总是要被改变，即使在 const 函数内
    mutable bool lengthIsValid;
};

std::size_t CTextBook::length() const
{
    if(!lengthIsValid)
    {
        textLength = std::strlen(pText);
        lengthIsValid = true;
    }
    return textLength;
}

#endif // CTEXTBOOK_H_
