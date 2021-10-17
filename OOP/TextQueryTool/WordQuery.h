#ifndef WORD_QUERY_H
#define WORD_QUERY_H

class WordQuery : public QueryBase
{
    friend class Query; // Query 需要使用 WordQuery 构造函数
    WordQuery(const std::string &s) : query_word(s) {}

    // WordQuery 将定义所以继承而来的虚函数
    QueryResult eval(const TextQuery &t) const
    {
        return t.query(query_word);
    }

    std::string rep() const { return query_word; }

    std::string query_word;
};

#endif //