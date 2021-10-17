#include "Query.h"


using namespace std;


inline Query::Query(const std::string &s) const :q(new WordQuery(s)){}



