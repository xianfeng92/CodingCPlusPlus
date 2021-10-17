#ifndef QUERY_H
#define QUERY_H

// Query 接口类，负责隐藏整个继承体系
// Query 将保存一个 Query_base 指针，该指针绑定到 Query_base 的派生类对象上
// Query 类与 Query_base 类提供的操作是相同的
// 这是一个管理 Query_base 继承体系的接口类
class Query
{
    // 这些运算符需要访问接受 shared_ptr 的构造函数，而该函数是私有的
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);

public:
    Query(const std::string &name); // 构建一个新的 WordQuery

    // 接口函数：调用对应的 Query_base 操作
    QueryResult eval(const TextQuery &t) const
    {
        return q->eval(t);
    }

    std::string rep() const
    {
        return q->rep();
    }

    std::ostream &operator<<(std::ostream &os, const Query &query)
    {
        return os << query.rep();
    }

private:
    Query(std::shared_ptr<QueryBase> query) : q(query) {}
    std::shared_ptr<QueryBase> q; //
};

#endif //