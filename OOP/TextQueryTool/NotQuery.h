#ifndef NOT_QUERY_H
#define NOT_QUERY_H

class NotQuery : public Query_base
{
    friend Query operator~(const Query &query);
    NotQuery(const Query &q) : query(q) {}

    // 具体的类：NotQuery 将定义所以继承而来的虚函数
    std::string rep() const { return "~ (" + query.rep() + ")"; }

    QueryResult eval(const TextQuery &query) const;

    Query query;
};

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

#endif //