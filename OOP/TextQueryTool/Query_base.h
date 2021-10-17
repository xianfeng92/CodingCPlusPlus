#ifndef QUERY_BASE_H
#define QUERY_BASE_H

class QueryBase
{
    // 因为 Query 需要调用 QueryBase 的虚函数，所以将Query 声明为 QueryBase 的友元
    friend class Query;

protected:
    using line_no = TestQuery::line_no;
    virtual ~QueryBase() = default;

private:
    virtual QueryResult eval(const TestQuery &) const = 0;
    virtual rstd::string rep() const = 0;
};
#endif //