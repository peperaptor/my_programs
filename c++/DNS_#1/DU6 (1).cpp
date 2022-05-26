#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
#include "ipaddress.h"
using namespace std;
#endif /* __PROGTEST__ */

//template <typename ipT>
class CRec
{
public:
    string name;
    string type;
    string serverName;
    CIPv4 ip4;
    CIPv6 ip6;
    int priority = 0;

    CRec()
    {
    }
    CRec(const CRec& src)
    {
        name = src.name;
        type = src.type;
        serverName = src.serverName;
        ip4 = src.ip4;
        ip6 = src.ip6;
        priority = src.priority;
    }
    /*CRec(const string n, const ipT i):name(n), ip(i)
    {
        type = "base";
    }*/
    const string Type()const
    {
        return type;
    }
    const string Name()const
    {
        return name;
    }
    virtual shared_ptr<CRec> getPtr() const
    {
        return make_shared<CRec>((*this));
        //return nullptr;
    }
    friend  ostream& operator << (ostream& os, const CRec& x);
};
ostream& operator << (ostream& os, const CRec& x)
{
    //"fit.cvut.cz\n"
//    " +- progtest A 147.32.232.142\n"
//    " +- progtest AAAA 2001:718:2:2902:0:1:2:3\n"
//    " +- courses A 147.32.232.158\n"
//    " +- courses A 147.32.232.160\n"
//    " +- courses A 147.32.232.159\n"
//    " +- progtest AAAA 2001:718:2:2902:1:2:3:4\n"
//    " +- courses MX 0 relay.fit.cvut.cz.\n"
//    " \\- courses MX 10 relay2.fit.cvut.cz.\n");
    if (x.type == "A")
    {
        return os << x.name << " " << x.type << " " << x.ip4;
    }
    if (x.type == "AAAA")
    {
        return os << x.name << " " << x.type << " " << x.ip6;
    }
    if (x.type == "MX")
    {
        return os << x.name << " " << x.type << " " << x.priority << " " << x.serverName;
    }
    return os << "aaaaaaaaaaaaaaaaa";
}

//template <typename ipT>
//ostream& operator << (ostream& os, const CRec<ipT>& x)
//{
//    return os << " " << x.name << " " << x.type << " " << x.ip;
//}

class CRecA :public CRec
{
private:
    string haha = "progtestHack";
public:
    CRecA(const string n, const CIPv4 i)
    {
        type = "A";
        name = n;
        ip4 = i;
    }
    CRecA(const CRec& src) : CRec(src)
    {
        /*ip4 = src.ip4;
        name = src.name;
        type = src.type;*/
    }
    shared_ptr<CRec> getPtr() const override
    {
        return make_shared<CRecA>((*this));
    }
};


class CRecAAAA :public CRec
{
private:
    string haha = "progtestHack";
public:
    CRecAAAA(const string n, const CIPv6 i)
    {
        type = "AAAA";
        name = n;
        ip6 = i;
    }
    CRecAAAA(const CRec& src) : CRec(src)
    {
        /*ip6 = src.ip6;
        name = src.name;
        type = src.type;*/
    }
    shared_ptr<CRec> getPtr() const override
    {
        return make_shared<CRecAAAA>((*this));
    }
};


class CRecMX :public CRec
{
private:
    string haha = "progtestHack";
public:
    CRecMX(const string n, const string s, const int p)
    {
        type = "MX";
        name = n;
        serverName = s;
        priority = p;
    }
    CRecMX(const CRec& src) : CRec(src)
    {
        /* type = "MX";
         name = src.name;
         serverName = src.serverName;
         priority = src.priority;*/
    }
    shared_ptr<CRec> getPtr() const override
    {
        return make_shared<CRecMX>((*this));
    }
};

class SearchResult
{
private:
    vector<shared_ptr<CRec>> data;
public:
    SearchResult()
    {}
    void Add(const shared_ptr<CRec> nv)
    {
        data.push_back(nv);
    }
    size_t Count() const
    {
        return data.size();
    }

    const CRec& operator[](const size_t n) const
    {
        if (n >= data.size() || n < 0)
        {
            ostringstream oss;
            oss << n;
            throw std::out_of_range(oss.str());
        }
        return (*(data.at(n)));
    }

    friend  ostream& operator << (ostream& os, const SearchResult& x);
};
ostream& operator << (ostream& os, const SearchResult& x)
{
    auto itCurr = x.data.begin();
    while (itCurr != x.data.end())
    {
        os << (*(*itCurr)) << endl;
        itCurr++;
    }
    return os;
}

class CZone
{
private:
    string name;
    vector<shared_ptr<CRec>> data;
    bool isSimilarCRec(const shared_ptr<CRec>& itCurr, const CRec& newElement)
    {
        if (itCurr->Type() == newElement.Type() && itCurr->ip4 == newElement.ip4 && itCurr->ip6 == newElement.ip6
            && itCurr->name == newElement.name && itCurr->serverName == newElement.serverName && itCurr->priority == newElement.priority)
        {
            return true;
        }
        return false;
    }
public:
    CZone(const string n)
    {
        name = n;
    }
    bool Add(const CRec& newElement)
    {
        auto itCurr = data.begin();;
        while (itCurr != data.end())
        {
            if (isSimilarCRec((*itCurr), newElement))
            {
                return false;
            }
            itCurr++;
        }

        shared_ptr<CRec> shrdp = newElement.getPtr();
        data.push_back(shrdp);
        return true;
    }
    bool Del(const CRec& elementToDel)
    {
        auto itCurr = data.begin();;
        while (itCurr != data.end())
        {
            if (isSimilarCRec((*itCurr), elementToDel))
            {
                data.erase(itCurr);
                return true;
            }
            itCurr++;
        }
        return false;
    }

    SearchResult Search(const string& val) const
    {
        SearchResult res;

        auto itCurr = data.begin();;
        while (itCurr != data.end())
        {
            if ((*itCurr)->Name() == val)
            {
                res.Add((*(*itCurr)).getPtr());
            }
            itCurr++;
        }
        return res;
    }
    friend  ostream& operator << (ostream& os, const CZone& x);
};
ostream& operator << (ostream& os, const CZone& x)
{
    os << x.name << endl;
    auto itCurr = x.data.begin();;
    while ((itCurr + 1) != x.data.end())
    {
        os << " +- " << (*(*itCurr)) << endl;
        itCurr++;
    }
    os << " \\- " << (*(*itCurr)) << endl;
    return os;
}
#ifndef __PROGTEST__
int main(void)
{
    ostringstream oss;

    CZone z0("fit.cvut.cz");
    assert(z0.Add(CRecA("progtest", CIPv4("147.32.232.142"))) == true);
    assert(z0.Add(CRecAAAA("progtest", CIPv6("2001:718:2:2902:0:1:2:3"))) == true);
    assert(z0.Add(CRecA("courses", CIPv4("147.32.232.158"))) == true);
    assert(z0.Add(CRecA("courses", CIPv4("147.32.232.160"))) == true);
    assert(z0.Add(CRecA("courses", CIPv4("147.32.232.159"))) == true);
    assert(z0.Add(CRecAAAA("progtest", CIPv6("2001:718:2:2902:1:2:3:4"))) == true);
    assert(z0.Add(CRecMX("courses", "relay.fit.cvut.cz.", 0)) == true);
    assert(z0.Add(CRecMX("courses", "relay2.fit.cvut.cz.", 10)) == true);
    oss.str("");
    oss << z0;

    //cout << z0 << endl;

    assert(oss.str() ==
        "fit.cvut.cz\n"
        " +- progtest A 147.32.232.142\n"
        " +- progtest AAAA 2001:718:2:2902:0:1:2:3\n"
        " +- courses A 147.32.232.158\n"
        " +- courses A 147.32.232.160\n"
        " +- courses A 147.32.232.159\n"
        " +- progtest AAAA 2001:718:2:2902:1:2:3:4\n"
        " +- courses MX 0 relay.fit.cvut.cz.\n"
        " \\- courses MX 10 relay2.fit.cvut.cz.\n");

    //cout << z0.Search("progtest") << endl;

    assert(z0.Search("progtest").Count() == 3);
    oss.str("");
    oss << z0.Search("progtest");
    assert(oss.str() ==
        "progtest A 147.32.232.142\n"
        "progtest AAAA 2001:718:2:2902:0:1:2:3\n"
        "progtest AAAA 2001:718:2:2902:1:2:3:4\n");
    assert(z0.Del(CRecA("courses", CIPv4("147.32.232.160"))) == true);
    assert(z0.Add(CRecA("courses", CIPv4("147.32.232.122"))) == true);
    oss.str("");
    oss << z0;
    assert(oss.str() ==
        "fit.cvut.cz\n"
        " +- progtest A 147.32.232.142\n"
        " +- progtest AAAA 2001:718:2:2902:0:1:2:3\n"
        " +- courses A 147.32.232.158\n"
        " +- courses A 147.32.232.159\n"
        " +- progtest AAAA 2001:718:2:2902:1:2:3:4\n"
        " +- courses MX 0 relay.fit.cvut.cz.\n"
        " +- courses MX 10 relay2.fit.cvut.cz.\n"
        " \\- courses A 147.32.232.122\n");
    assert(z0.Search("courses").Count() == 5);
    oss.str("");
    oss << z0.Search("courses");
    assert(oss.str() ==
        "courses A 147.32.232.158\n"
        "courses A 147.32.232.159\n"
        "courses MX 0 relay.fit.cvut.cz.\n"
        "courses MX 10 relay2.fit.cvut.cz.\n"
        "courses A 147.32.232.122\n");
    oss.str("");

    //cout << z0.Search("courses")[0] << endl;
    oss << z0.Search("courses")[0];

    assert(oss.str() == "courses A 147.32.232.158");
    assert(z0.Search("courses")[0].Name() == "courses");
    assert(z0.Search("courses")[0].Type() == "A");
    oss.str("");
    oss << z0.Search("courses")[1];
    assert(oss.str() == "courses A 147.32.232.159");
    assert(z0.Search("courses")[1].Name() == "courses");
    assert(z0.Search("courses")[1].Type() == "A");
    oss.str("");
    oss << z0.Search("courses")[2];
    assert(oss.str() == "courses MX 0 relay.fit.cvut.cz.");
    assert(z0.Search("courses")[2].Name() == "courses");
    assert(z0.Search("courses")[2].Type() == "MX");
    try
    {
        oss.str("");
        oss << z0.Search("courses")[10];
        assert("No exception thrown!" == nullptr);
    }
    catch (const out_of_range& e)
    {
    }
    catch (...)
    {
        assert("Invalid exception thrown!" == nullptr);
    }

    cout << z0.Search("progtest")[1];

    dynamic_cast<const CRecAAAA&> (z0.Search("progtest")[1]);

    CZone z1("fit2.cvut.cz");
    z1.Add(z0.Search("progtest")[2]);
    z1.Add(z0.Search("progtest")[0]);
    z1.Add(z0.Search("progtest")[1]);
    z1.Add(z0.Search("courses")[2]);
    oss.str("");
    oss << z1;
    assert(oss.str() ==
        "fit2.cvut.cz\n"
        " +- progtest AAAA 2001:718:2:2902:1:2:3:4\n"
        " +- progtest A 147.32.232.142\n"
        " +- progtest AAAA 2001:718:2:2902:0:1:2:3\n"
        " \\- courses MX 0 relay.fit.cvut.cz.\n");

    dynamic_cast<const CRecA&> (z1.Search("progtest")[1]);

    CZone z2("fit.cvut.cz");
    assert(z2.Add(CRecA("progtest", CIPv4("147.32.232.142"))) == true);
    assert(z2.Add(CRecAAAA("progtest", CIPv6("2001:718:2:2902:0:1:2:3"))) == true);
    assert(z2.Add(CRecA("progtest", CIPv4("147.32.232.144"))) == true);
    assert(z2.Add(CRecMX("progtest", "relay.fit.cvut.cz.", 10)) == true);
    assert(z2.Add(CRecA("progtest", CIPv4("147.32.232.142"))) == false);
    assert(z2.Del(CRecA("progtest", CIPv4("147.32.232.140"))) == false);
    assert(z2.Del(CRecA("progtest", CIPv4("147.32.232.142"))) == true);
    assert(z2.Del(CRecA("progtest", CIPv4("147.32.232.142"))) == false);
    assert(z2.Add(CRecMX("progtest", "relay.fit.cvut.cz.", 20)) == true);
    assert(z2.Add(CRecMX("progtest", "relay.fit.cvut.cz.", 10)) == false);
    oss.str("");
    oss << z2;
    assert(oss.str() ==
        "fit.cvut.cz\n"
        " +- progtest AAAA 2001:718:2:2902:0:1:2:3\n"
        " +- progtest A 147.32.232.144\n"
        " +- progtest MX 10 relay.fit.cvut.cz.\n"
        " \\- progtest MX 20 relay.fit.cvut.cz.\n");
    assert(z2.Search("progtest").Count() == 4);
    oss.str("");
    oss << z2.Search("progtest");
    assert(oss.str() ==
        "progtest AAAA 2001:718:2:2902:0:1:2:3\n"
        "progtest A 147.32.232.144\n"
        "progtest MX 10 relay.fit.cvut.cz.\n"
        "progtest MX 20 relay.fit.cvut.cz.\n");
    assert(z2.Search("courses").Count() == 0);
    oss.str("");
    oss << z2.Search("courses");
    assert(oss.str() == "");
    try
    {
        dynamic_cast<const CRecMX&> (z2.Search("progtest")[0]);
        assert("Invalid type" == nullptr);
    }
    catch (const bad_cast& e)
    {
    }

    CZone z4("fit.cvut.cz");
    assert(z4.Add(CRecA("progtest", CIPv4("147.32.232.142"))) == true);
    assert(z4.Add(CRecA("courses", CIPv4("147.32.232.158"))) == true);
    assert(z4.Add(CRecA("courses", CIPv4("147.32.232.160"))) == true);
    assert(z4.Add(CRecA("courses", CIPv4("147.32.232.159"))) == true);
    CZone z5(z4);
    assert(z4.Add(CRecAAAA("progtest", CIPv6("2001:718:2:2902:0:1:2:3"))) == true);
    assert(z4.Add(CRecAAAA("progtest", CIPv6("2001:718:2:2902:1:2:3:4"))) == true);
    assert(z5.Del(CRecA("progtest", CIPv4("147.32.232.142"))) == true);
    oss.str("");
    oss << z4;
    assert(oss.str() ==
        "fit.cvut.cz\n"
        " +- progtest A 147.32.232.142\n"
        " +- courses A 147.32.232.158\n"
        " +- courses A 147.32.232.160\n"
        " +- courses A 147.32.232.159\n"
        " +- progtest AAAA 2001:718:2:2902:0:1:2:3\n"
        " \\- progtest AAAA 2001:718:2:2902:1:2:3:4\n");
    oss.str("");
    oss << z5;
    assert(oss.str() ==
        "fit.cvut.cz\n"
        " +- courses A 147.32.232.158\n"
        " +- courses A 147.32.232.160\n"
        " \\- courses A 147.32.232.159\n");
    z5 = z4;
    assert(z4.Add(CRecMX("courses", "relay.fit.cvut.cz.", 0)) == true);
    assert(z4.Add(CRecMX("courses", "relay2.fit.cvut.cz.", 10)) == true);
    oss.str("");
    oss << z4;
    assert(oss.str() ==
        "fit.cvut.cz\n"
        " +- progtest A 147.32.232.142\n"
        " +- courses A 147.32.232.158\n"
        " +- courses A 147.32.232.160\n"
        " +- courses A 147.32.232.159\n"
        " +- progtest AAAA 2001:718:2:2902:0:1:2:3\n"
        " +- progtest AAAA 2001:718:2:2902:1:2:3:4\n"
        " +- courses MX 0 relay.fit.cvut.cz.\n"
        " \\- courses MX 10 relay2.fit.cvut.cz.\n");
    oss.str("");
    oss << z5;
    assert(oss.str() ==
        "fit.cvut.cz\n"
        " +- progtest A 147.32.232.142\n"
        " +- courses A 147.32.232.158\n"
        " +- courses A 147.32.232.160\n"
        " +- courses A 147.32.232.159\n"
        " +- progtest AAAA 2001:718:2:2902:0:1:2:3\n"
        " \\- progtest AAAA 2001:718:2:2902:1:2:3:4\n");

    return 0;
}
#endif /* __PROGTEST__ */
