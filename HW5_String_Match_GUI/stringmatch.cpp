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
    size_t l = model.size();
    std::string s = model;

    for (int i = 0, j = l - 1; i < j; ++i, --j)
    {
        char ch = s[i];
        s[i] = s[j];
        s[j] = ch;
    }

    // kmp-fail

    int* fail = new int[l];
    fail[0] = -1;
    for (size_t i = 1; i < l; ++i)
    {
        int cur = fail[i - 1];
        while (cur != -1 && s[cur + 1] != s[i]) cur = fail[cur];
        if (s[cur + 1] == s[i]) fail[i] = cur + 1; else fail[i] = -1;
    }

    // osuff

    int* osuff = new int[l];
    //bool* used = new bool[l];
    for (size_t i = 0; i < l; ++i)
    {
        osuff[i] = -1;
        //used[i] = false;
    }
    for (int i = l - 1; i >= 0; --i)
    {
        int cur = i;
        while (fail[cur] != -1)
        {
            //used[cur] = true;
            //if (fail[cur] == -1) break;
            //if (osuff[i - fail[cur]] != -1) break;
            osuff[i - fail[cur]] = fail[cur];
            cur = fail[cur];
        }
    }
    osuff[0] = l - 1;
    for (int i = 0, j = l - 1; i < j; ++i, --j)
    {
        int tmp = osuff[i];
        osuff[i] = osuff[j];
        osuff[j] = tmp;
    }

    // bmBc

    int* bmBc = new int[128];
    for (int i = 0; i < 128; ++i) bmBc[i] = l;
    for (size_t i = 0; i < l - 1; ++i) bmBc[(int)model[i]] = (int)l - i - 1;

    // bmGs

    int* bmGs = new int[l];
    for (size_t i = 0; i < l; ++i) bmGs[i] = l;
    size_t jj = 0;
    for (int i = l - 2; i >= 0; --i)
    {
        if (osuff[i] == i)
        {
            while (jj <= l - 1 - i - 1)
            {
                if (bmGs[jj] == (int)l) bmGs[jj] = l - i - 1;
                ++jj;
            }
        }
    }
    for (size_t i = 0; i < l - 1; ++i) bmGs[l - osuff[i] - 2] = l - i - 1;

    // bm

    std::vector<int> result;
    int cur = 0;
    while (cur <= (int)(len - l))
    {
        int match = l - 1;
        while (model[match] == st[cur + match])
        {
            if (match == 0)
            {
                result.push_back(cur);
                break;
            }
            else
            {
                --match;
            }
        }
        int xx = bmGs[match];
        int yy = bmBc[(int)st[cur + match]] - (int)len + match;
        if (xx > yy) cur += xx; else cur += yy;
    }

    delete[] fail;
    delete[] osuff;
    //delete[] used;
    delete[] bmBc;
    delete[] bmGs;

    return result;
}
