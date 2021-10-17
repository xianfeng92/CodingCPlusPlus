
#ifndef BLOB_H
#define BLOB_H
#include<string>
#include<vector>
#include<memory>

// 当用户实例化 Blob 时，T 会被替换成特定的模版实参类型
template <typename T>
class Blob
{
public:
    typedef T type_vale;
    typedef typename std::vector<T>::size_type size_type;
    Blob() = default;
    Blob(std::initializer_list<T> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &t) { data->push_back(t); }
    void push_back(const T &&t) { data->push_back(std::move(t)); }
    void pop_back();

    T &back();
    T &operator[](size_type i);

private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
}

#endif //