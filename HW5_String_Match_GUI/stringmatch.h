#ifndef STRINGMATCH_H
#define STRINGMATCH_H

#include <string>
#include <vector>

class StringMatch
{
private:
    std::string st;
    size_t len;

public:
    StringMatch(const std::string& _st);
    ~StringMatch();

public:
    std::vector<int> matchBF(const std::string& model);
    std::vector<int> matchKMP(const std::string& model);
    std::vector<int> matchBM(const std::string& model);
};

#endif // STRINGMATCH_H
