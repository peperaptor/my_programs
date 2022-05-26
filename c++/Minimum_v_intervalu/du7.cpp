#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <forward_list>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>

using namespace std;
#endif /* __PROGTEST__ */


template<typename T_, typename Cmp_ = std::less<T_>>
class CIntervalMin
{
private:
    Cmp_ myCmp;
    vector<T_> data;
    //std::function<bool(const T_& left, const T_& right)> = std::less<T_>;
    
public:
    CIntervalMin()
    {

    }
    template<typename ncmp>
    CIntervalMin(ncmp newCmp):myCmp(newCmp)
    {
        //myCmp = newCmp;
    }
    template <typename _Iter>
    CIntervalMin(const _Iter b, const _Iter e)
    {
        auto curr = b;
        while (curr != e)
        {
            data.push_back(T_((*curr)));
            curr++;
        }
    }
    template<typename _iter, typename  ncmp>
    CIntervalMin(const _iter b, const _iter e, ncmp newcmp) :myCmp(newcmp)
    {
        //myCmp = newcmp;
        auto curr = b;
        while (curr != e)
        {
            push_back((*curr));
            curr++;
        }
    }

    // const_iterator
    void push_back(const T_ & val)
    {
        data.push_back(val);
    }
    void pop_back()
    {
        data.pop_back();
    }
    // min
    typename std::vector<T_>::const_iterator begin()
    {
        return data.begin();
    }
    typename std::vector<T_>::const_iterator end()
    {
        return data.end();
    }
    size_t size()
    {
        return data.size();
    }

    T_ min(const typename std::vector<T_>::const_iterator b, const typename std::vector<T_>::const_iterator e)
    {
        if (b == e)
        {
            throw std::invalid_argument("aaaaaa");
        }
        auto beg = b;
        T_ min = (*beg);
        while (beg != e)
        {
            if (myCmp((*beg), min))
            {
                min = (*beg);
            }
            beg++;
        }
        return min;
    }
};


#ifndef __PROGTEST__
//-------------------------------------------------------------------------------------------------
class CStrComparator
{
public:
    CStrComparator(bool byLength = true)
        : m_ByLength(byLength)
    {
    }
    bool       operator () (const string& a, const string& b) const
    {
        return m_ByLength ? a.length() < b.length() : a < b;
    }
private:
    bool       m_ByLength;
};
//-------------------------------------------------------------------------------------------------
bool strCaseCmpFn(const string& a, const string& b)
{
    string aa;
    for (size_t i = 0; i < a.length(); i++)
    {
        aa += tolower(a[i]);
    }
    string bb;
    for (size_t i = 0; i < b.length(); i++)
    {
        bb += tolower(b[i]);
    }
    return strcmp(aa.c_str(), bb.c_str()) < 0;
}
bool antiless(const int & a, const int& b)
{
    return a > b;
}
//-------------------------------------------------------------------------------------------------
int main(void)
{
    //CIntervalMin <int, bool(*)(const int& a, const int& b)> a1(antiless);
    //a1.push_back(10);
    //a1.push_back(8);
    //a1.push_back(20);
    //a1.push_back(60);
    //a1.push_back(11);
    //cout << a1.min(a1.begin(), a1.end());

    //vector<string> words{ "auto", "if", "void", "NULL" };
    //CIntervalMin <string> a2(words.begin(), words.end());
    //cout << a2.min(a2.begin(), a2.end());


    CIntervalMin <int> a1;
     for (auto x : initializer_list<int>{ 5, 15, 79, 62, -3, 0, 92, 16, 2, -4 })
         a1.push_back(x);

     assert(a1.size() == 10);

     ostringstream oss;
     for (auto x : a1)
         oss << x << ' ';

     assert(oss.str() == "5 15 79 62 -3 0 92 16 2 -4 ");
     assert(a1.min(a1.begin(), a1.end()) == -4);
     assert(a1.min(a1.begin() + 2, a1.begin() + 3) == 79);
     assert(a1.min(a1.begin() + 2, a1.begin() + 9) == -3);

     try
     {
         a1.min(a1.begin(), a1.begin());
         assert("Missing an exception" == nullptr);
     }
     catch (const invalid_argument& e)
     {
     }
     catch (...)
     {
         assert("Invalid exception" == nullptr);
     }

     a1.pop_back();
     assert(a1.size() == 9);
     a1.push_back(42);

     assert(a1.min(a1.begin(), a1.end()) == -3);

     vector<string> words{ "auto", "if", "void", "NULL" };
     CIntervalMin <string> a2(words.begin(), words.end());
     assert(a2.min(a2.begin(), a2.end()) == "NULL");

     CIntervalMin <string, bool(*)(const string&, const string&)> a3(words.begin(), words.end(), strCaseCmpFn);
     assert(a3.min(a3.begin(), a3.end()) == "auto");

     CIntervalMin <string, CStrComparator> a4(words.begin(), words.end());
     assert(a4.min(a4.begin(), a4.end()) == "if");

     CIntervalMin <string, CStrComparator> a5(words.begin(), words.end(), CStrComparator(false));
     assert(a5.min(a5.begin(), a5.end()) == "NULL");

     CIntervalMin <string, function<bool(const string&, const string&)> > a6([](const string& a, const string& b)
         {
             return a > b;
         });
     for (const auto& w : words)
         a6.push_back(w);
     assert(a6.min(a6.begin(), a6.end()) == "void");
     //cout << 1;
    return 0;
}
#endif /* __PROGTEST__ */
