#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;

enum class ERel
{
    REL_NONE,
    REL_FATHER,
    REL_MOTHER,
    REL_SON,
    REL_DAUGHTER
};
#endif /* __PROGTEST__ */
class people
{
public:
    int id = 0;
    string name = "";
    //gender gend;
    shared_ptr<people> mother = nullptr;
    shared_ptr<people> father = nullptr;
    //vector<shared_ptr<people>> childrens;
    people()
    {

    }
    people(const people& src) :id(src.id), name(src.name), mother(src.mother), father(src.father)
    {

    }
    people(const int& i, const string& n) :id(i), name(n)
    {

    }
    //virtual ~people()
    //{

    //}
    int GetID() const
    {
        return id;
    }
    virtual void PrintDescendants(ostream& os) = 0;
    virtual bool IsMyName(const string& prefix) = 0;
    friend ostream& operator << (ostream& os, const people& p);
    virtual ostream& print(ostream& os) const
    {
        os << "isho";
        return os;
    }
};
ostream& operator << (ostream& os, const people& p)
{
    return p.print(os);
}

bool myCmpId(const shared_ptr<people> u1, const shared_ptr<people> u2)
{
    return u1->GetID() < u2->GetID();
}

class CMan : public people
{
private:
    // todo
public:
    CMan()
    {

    }
    CMan(const CMan& src) :people(src)
    {

    }
    CMan(const int& i, const string& n)
    {
        id = i;
        name = n;
    }
    // GetID ()
    // operator <<
    // void PrintDescendants ( os )
    void PrintDescendants(ostream& os) override
    {

    }
    bool IsMyName(const string& prefix) override
    {
        return name.find(prefix) != string::npos;
    }
    virtual ostream& print(ostream& os) const
    {
        os << GetID() << ": " << name << " " << "(man)";
        return os;
    }
};

class CWoman : public people
{
private:
    vector<string> nameHistory;
public:
    CWoman()
    {

    }
    CWoman(const CWoman& src) :people(src)
    {
        nameHistory = src.nameHistory;
    }
    CWoman(const int& i, const string& n)
    {
        id = i;
        name = n;
    }

    void Wedding(const string& newName)
    {
        nameHistory.push_back(name);
        name = newName;
    }
    void PrintDescendants(ostream& os) override
    {

    }
    bool IsMyName(const string& prefix) override
    {
        if (name.find(prefix) != string::npos)
        {
            return true;
        }
        for (auto i = nameHistory.begin(); i != nameHistory.end(); i++)
        {
            if ((*i).find(prefix) != string::npos)
            {
                return true;
            }
        }
        return false;
    }
    virtual ostream& print(ostream& os) const
    {
        os << GetID() << ": ";
        if (nameHistory.size() > 0)
        {
            os << name << " [";
            for (auto curr = nameHistory.begin(); curr != nameHistory.end(); curr++)
            {
                os << (*curr);
                if (curr + 1 != nameHistory.end())
                {
                    os << ", ";
                }
            }
            os << "]";
        }
        else
        {
            os << name;
        }
        os << " (woman)";
        return os;
    }
};

class CRegister
{
private:
    //vector<shared_ptr<people>> peoplesById;
    map<int, shared_ptr<people>> idPeople;
public:
    CRegister()
    {

    }
    bool Add(const shared_ptr<people> newPerson, const shared_ptr<people> father, const shared_ptr<people> mother)
    {
        if (idPeople.count(newPerson->GetID()) > 0)
        {
            return false;
        }
        idPeople[newPerson->GetID()] = newPerson;



        //if (peoplesById.size() < 1)
        //{
        //    peoplesById.push_back(newPerson);
        //    return true;
        //}
        //if (binary_search(peoplesById.begin(), peoplesById.end(), newPerson, myCmpId))
        //{
        //    return false;
        //}
        //auto p = lower_bound(peoplesById.begin(), peoplesById.end(), newPerson, myCmpId);
        //if (p != peoplesById.end())
        //{
        //    return false;
        //}


        ////newPerson->mother = mother;
        ////newPerson->father = father;
        //peoplesById.insert(p, newPerson);
        return true;
    }
    const shared_ptr<people> FindByID(const int& id) const
    {
        if (idPeople.count(id) == 0)
        {
            return nullptr;
        }
        return idPeople.find(id)->second;
        /*shared_ptr<CMan> tmp = make_shared<CMan>(CMan(id, "aaa"));
        auto p = lower_bound(peoplesById.begin(), peoplesById.end(), tmp, myCmpId);
        if ((*p)->GetID() != id)
        {
            return nullptr;
        }
        if (p == peoplesById.end())
        {
            return nullptr;
        }
        return (*p);*/
    }
    vector<shared_ptr<people>> FindByName(const string& prefix) const
    {
        vector<shared_ptr<people>> res;
        auto curr = idPeople.begin();
        while (curr != idPeople.end())
        {
            if ((*curr).second->IsMyName(prefix))
            {
                res.push_back((*curr).second);
            }
            curr++;
        }
        return res;
    }
    list<pair<shared_ptr<people>, ERel> > FindRelatives(const int& id1, const int& id2) const
    {
        list<pair<shared_ptr<people>, ERel> > res;
        return res;
    }

};

#ifndef __PROGTEST__
template <typename T_>
static bool        vectorMatch(const vector<T_>& res,
    const vector<string>& ref)
{
    vector<string> tmp;
    for (const auto& x : res)
    {
        ostringstream oss;
        oss << *x;
        //cout << *x << "\n";
        tmp.push_back(oss.str());
    }
    return tmp == ref;
}
template <typename T_>
static bool        listMatch(const list<pair<T_, ERel> >& res,
    const list<pair<string, ERel> >& ref)
{
    list<pair<string, ERel> > tmp;
    for (const auto& x : res)
    {
        ostringstream oss;
        oss << *x.first;
        tmp.emplace_back(oss.str(), x.second);
    }
    return tmp == ref;
}
int main(void)
{
    ostringstream oss;
    CRegister r;
    assert(r.Add(make_shared<CMan>(1, "Peterson George"),
        nullptr, nullptr) == true);
    assert(r.Add(make_shared<CMan>(2, "Watson Paul"),
        nullptr, nullptr) == true);
    assert(r.Add(make_shared<CMan>(10, "Smith Samuel"),
        nullptr, nullptr) == true);
    assert(r.Add(make_shared<CWoman>(11, "Peterson Jane"),
        r.FindByID(1), nullptr) == true);
    assert(r.Add(make_shared<CWoman>(12, "Peterson Sue"),
        r.FindByID(1), nullptr) == true);
    assert(r.Add(make_shared<CMan>(13, "Pershing John"),
        nullptr, nullptr) == true);
    assert(r.Add(make_shared<CMan>(14, "Pearce Joe"),
        nullptr, nullptr) == true);
    assert(r.Add(make_shared<CMan>(15, "Peant Thomas"),
        nullptr, nullptr) == true);
    assert(r.Add(make_shared<CMan>(100, "Smith John"),
        r.FindByID(10), r.FindByID(11)) == true);
    assert(r.Add(make_shared<CMan>(101, "Smith Roger"),
        r.FindByID(10), r.FindByID(11)) == true);
    assert(r.Add(make_shared<CMan>(102, "Smith Daniel"),
        r.FindByID(10), r.FindByID(11)) == true);
    assert(r.Add(make_shared<CWoman>(103, "Smith Eve"),
        r.FindByID(10), r.FindByID(11)) == true);
    assert(r.Add(make_shared<CWoman>(103, "Smith Jane"),
        r.FindByID(10), r.FindByID(11)) == false);
    dynamic_cast<CWoman&> (*r.FindByID(12)).Wedding("Smith Sue");
    assert(r.Add(make_shared<CMan>(150, "Pershing Joe"),
        r.FindByID(13), r.FindByID(12)) == true);
    dynamic_cast<CWoman&> (*r.FindByID(12)).Wedding("Pearce Sue");
    assert(r.Add(make_shared<CMan>(151, "Pearce Phillip"),
        r.FindByID(14), r.FindByID(12)) == true);
    dynamic_cast<CWoman&> (*r.FindByID(12)).Wedding("Peant Sue");
    assert(r.Add(make_shared<CMan>(152, "Peant Harry"),
        r.FindByID(15), r.FindByID(12)) == true);
    assert(r.Add(make_shared<CMan>(200, "Pershing Peter"),
        r.FindByID(150), r.FindByID(103)) == true);
    assert(r.Add(make_shared<CWoman>(201, "Pershing Julia"),
        r.FindByID(150), r.FindByID(103)) == true);
    assert(r.Add(make_shared<CWoman>(202, "Pershing Anne"),
        r.FindByID(150), r.FindByID(103)) == true);


    //assert(r.Add(make_shared<CMan>(2022, "Oleg Oleg"),
    //    r.FindByID(150), r.FindByID(103)) == true);

    //r.FindByName("Oleg");

    assert(vectorMatch(r.FindByName("Peterson"), vector<string>
    {
        "1: Peterson George (man)",
            "11: Peterson Jane (woman)",
            "12: Peant Sue [Peterson Sue, Smith Sue, Pearce Sue] (woman)"
    }));

    assert(vectorMatch(r.FindByName("Pe"), vector<string>
    {
        "1: Peterson George (man)",
            "11: Peterson Jane (woman)",
            "12: Peant Sue [Peterson Sue, Smith Sue, Pearce Sue] (woman)",
            "13: Pershing John (man)",
            "14: Pearce Joe (man)",
            "15: Peant Thomas (man)",
            "150: Pershing Joe (man)",
            "151: Pearce Phillip (man)",
            "152: Peant Harry (man)",
            "200: Pershing Peter (man)",
            "201: Pershing Julia (woman)",
            "202: Pershing Anne (woman)"
    }));

    assert(vectorMatch(r.FindByName("Smith"), vector<string>
    {
        "10: Smith Samuel (man)",
            "12: Peant Sue [Peterson Sue, Smith Sue, Pearce Sue] (woman)",
            "100: Smith John (man)",
            "101: Smith Roger (man)",
            "102: Smith Daniel (man)",
            "103: Smith Eve (woman)"
    }));
    assert(r.FindByID(1)->GetID() == 1);
    oss.str("");
    oss << *r.FindByID(1);
    assert(oss.str() == "1: Peterson George (man)");
    oss.str("");
    //r.FindByID(1)->PrintDescendants(oss);
    //assert(oss.str() ==
    //    "1: Peterson George (man)\n"
    //    " +- 11: Peterson Jane (woman)\n"
    //    " |  +- 100: Smith John (man)\n"
    //    " |  +- 101: Smith Roger (man)\n"
    //    " |  +- 102: Smith Daniel (man)\n"
    //    " |  \\- 103: Smith Eve (woman)\n"
    //    " |     +- 200: Pershing Peter (man)\n"
    //    " |     +- 201: Pershing Julia (woman)\n"
    //    " |     \\- 202: Pershing Anne (woman)\n"
    //    " \\- 12: Peant Sue [Peterson Sue, Smith Sue, Pearce Sue] (woman)\n"
    //    "    +- 150: Pershing Joe (man)\n"
    //    "    |  +- 200: Pershing Peter (man)\n"
    //    "    |  +- 201: Pershing Julia (woman)\n"
    //    "    |  \\- 202: Pershing Anne (woman)\n"
    //    "    +- 151: Pearce Phillip (man)\n"
    //    "    \\- 152: Peant Harry (man)\n");
    //assert(r.FindByID(2)->GetID() == 2);
    //oss.str("");
    //oss << *r.FindByID(2);
    //assert(oss.str() == "2: Watson Paul (man)");
    //oss.str("");
    //r.FindByID(2)->PrintDescendants(oss);
    //assert(oss.str() ==
    //    "2: Watson Paul (man)\n");
    //assert(listMatch(r.FindRelatives(100, 1), list<pair<string, ERel> >
    //{
    //    { "11: Peterson Jane (woman)", ERel::REL_MOTHER },
    //    { "1: Peterson George (man)", ERel::REL_FATHER }
    //}));
    //assert(listMatch(r.FindRelatives(100, 13), list<pair<string, ERel> >
    //{
    //    { "10: Smith Samuel (man)", ERel::REL_FATHER },
    //    { "103: Smith Eve (woman)", ERel::REL_DAUGHTER },
    //    { "200: Pershing Peter (man)", ERel::REL_SON },
    //    { "150: Pershing Joe (man)", ERel::REL_FATHER },
    //    { "13: Pershing John (man)", ERel::REL_FATHER }
    //}));
    //assert(listMatch(r.FindRelatives(100, 2), list<pair<string, ERel> >
    //{
    //}));
    //try
    //{
    //    r.FindRelatives(100, 3);
    //    assert("Missing an exception" == nullptr);
    //}
    //catch (const invalid_argument& e)
    //{
    //}
    //catch (...)
    //{
    //    assert("An unexpected exception thrown");
    //}
    //try
    //{
    //    r.FindRelatives(100, 100);
    //    assert("Missing an exception" == nullptr);
    //}
    //catch (const invalid_argument& e)
    //{
    //}
    //catch (...)
    //{
    //    assert("An unexpected exception thrown");
    //}
    return 0;
}
#endif /* __PROGTEST__ */
