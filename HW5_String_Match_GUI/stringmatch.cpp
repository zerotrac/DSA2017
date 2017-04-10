#include "stringmatch.h"

StringMatch::StringMatch(const std::string& _st)
{
    st = _st;
    len = st.size();
}

StringMatch::~StringMatch()
{
    // do nothing
}

std::vector<int> StringMatch::matchBF(const std::string& model)
{
    std::vector<int> result;

    for (size_t i = 0; i <= len - model.size(); ++i)
    {
        bool flag = true;
        for (size_t j = 0; j < model.size(); ++j)
        {
            if (st[i + j] != model[j])
            {
                flag = false;
                break;
            }
        }
        if (flag) result.push_back(i);
    }
    return result;
}

std::vector<int> StringMatch::matchKMP(const std::string& model)
{
    int* fail = new int[model.size()];
    fail[0] = -1;
    for (size_t i = 1; i < model.size(); ++i)
    {
        int pos = fail[i - 1];
        while (pos != -1 && model[pos + 1] != model[i]) pos = fail[pos];
        if (model[pos + 1] == model[i]) fail[i] = pos + 1; else fail[i] = -1;
    }

    std::vector<int> result;
    int cur = -1;
    for (size_t i = 0; i < len; ++i)
    {
        while (cur != -1 && model[cur + 1] != st[i]) cur = fail[cur];
        if (model[cur + 1] == st[i]) ++cur;
        if (cur == (int)model.size() - 1)
        {
            result.push_back(i - model.size() + 1);
            cur = fail[cur];
        }
    }

    delete[] fail;
    return result;
}

std::vector<int> StringMatch::matchBM(const std::string& model)
{

}
