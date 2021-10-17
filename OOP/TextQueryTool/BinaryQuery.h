#ifndef BINARY_QUERY_H
#define BINARY_QUERY_H

class BinaryQuery : public QueryBase
{
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s) : lhs(l), rhs(r), opSys(s) {}

    std::string rep() const
    {
        return "(" + lhs.rep() + " " + opSys + " " + rhs.rep() + ")";
    }

    Query lhs, rhs;
    std::string opSys;
};

#endif