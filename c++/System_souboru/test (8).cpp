
#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <cstdint>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */


class obj
{
private:
public:
    obj(){}
    obj(const obj & src) 
    {
        
    }
    virtual const size_t Size() const = 0;
    virtual const string val() = 0;
};

class CFile:public obj
{
private:
    size_t size = 0;
    string hash;
public:
    CFile(const CFile &src): obj(src) 
    {
        hash = src.hash;
        size = src.size;
    }
    CFile(string hsh, size_t sz)
    {
        hash = hsh;
        size = sz;
    }

    const size_t Size() const override
    {
        return size;
    }

    CFile& Change(string hsh, size_t sz)
    {
        hash = hsh;
        size = sz;
        return *this;
    }
    const string val() override
    {
        return hash;
    }
};


class CLink:public obj
{
    string path;
public:
    CLink(const CLink &src): obj(src) 
    {
        path = src.path;
    }
    CLink(string pth)
    {
        path = pth;
    }

    const size_t Size() const override
    {
        return path.size() + 1;
    }

    CLink& Change (const string pth)
    {
        path = pth;
        return *this;
    }
    const string val() override
    {
        return path;
    }
};


class CDirectory:public obj
{
private:
    map<string, shared_ptr<obj>> dirs;
public:
    CDirectory()
    {
    }
    CDirectory(const CDirectory &src): obj(src) 
    {
        dirs.clear();
        dirs.insert(src.dirs.begin(), src.dirs.end());
    }
    ~CDirectory()
    {

    }
    const size_t Size() const override 
    {
        size_t res = 0;
        auto it = dirs.begin();
        while (it != dirs.end())
        {
            res += it->second->Size() + it->first.size();
            it ++;
        }
        return res;
    }


    CDirectory& Change(const string filename, const obj &file)
    {
        if (const CFile* pfile = dynamic_cast <const CFile*>( &file )  )
        {
            dirs[filename] =  (shared_ptr<obj>(new CFile(*pfile)));
        }
        if (const CLink* pfile = dynamic_cast <const CLink*>( &file )  )
        {
            dirs[filename] =  (shared_ptr<obj>(new CLink(*pfile)));
        }
        if (const CDirectory* pfile = dynamic_cast <const CDirectory*>( &file )  )
        {
            dirs[filename] =  (shared_ptr<obj>(new CDirectory(*pfile)));
        }
        return *this;
    }

    CDirectory& Change(const string filename, nullptr_t null)
    {
        dirs.erase(filename);
        return *this;
    }

    obj& Get(const string filename) const
    {
        if (dirs.find(filename) != dirs.end())
        {
            return *dirs.find(filename)->second;
        }
        throw out_of_range("out_of_range");
    }

    friend ostream& operator<< (ostream &out, const CDirectory &dir);
    const string val() override
    {
        return "";
    }
};

ostream& operator<< (ostream &out, const CDirectory &dir)
{
    set<string> names;
    auto it = dir.dirs.begin();
    while (it != dir.dirs.end())
    {
        names.insert(it->first);
        it ++;
    }
    auto itt = names.begin();
    for (size_t i = 0; itt != names.end(); itt ++, i++) 
    { 
        if (dynamic_pointer_cast <CFile>( dir.dirs.find((*itt))->second )  )
        {
            out << (*dir.dirs.find((*itt))->second).Size() << "\t"
                << (*itt) << " " 
                    << (*dir.dirs.find((*itt))->second).val() << "\n";
        }
        if (dynamic_pointer_cast <CLink>( dir.dirs.find((*itt))->second ) )
        {
            out << (*dir.dirs.find((*itt))->second).Size() << "\t"
                 << (*itt) << " -> " 
                    << (*dir.dirs.find((*itt))->second).val() << "\n";
        }
        if (dynamic_pointer_cast <CDirectory>( dir.dirs.find((*itt))->second ) )
        {
            out << (*dir.dirs.find((*itt))->second).Size() << "\t" << (*itt)  << "/\n";
        }
    }
    return out;
}

#ifndef __PROGTEST__
int main ()
{
    // CFile a("asdasdas=", 1623);
    // CFile b(a);
    // a.print();
    // b.print();
    // cout << endl;
    // a.Change("bbbbbbbbb=", 543);
    // a.print();
    // b.print();
    // b = a;
    // cout << endl;
    // a.print();
    // b.print();


    // CLink a("lasldl/asda/asd/asdasdasda.ads/dasda");
    // a.print();
    // CLink b(a);
    // b.print();
    // a.Change("lasldl/asdasdadsads/asd/fgadfgdfgdgf.ads/dasda", 123);
    // a.print();
    // b.print();


    // CDirectory a;
    // a.Change("file.txt", CFile("jhwadkhawkdhajwdhawhdaw=", 1623));
    // a.Change("filedasd.txt", CFile("jhwadkhawkdhajwdhawhdaw=", 1623));
    // a.Change("file.ln", CLink("file.txt"));
    // // a.Change
    // // ("folder", 
    // //     CDirectory().Change("fileA.txt", 
    // //         CFile("", 0).Change("skjdajdakljdljadkjwaljdlaw=", 1713)
    // //     )
    // // );
    // CDirectory b;
    // b.Change("dddddd",CFile("asdasdads", 1488));
    // a.Change("folder", b);
    // a.print();

    // CDirectory root;

    // // root.Change("file.txt", CFile("jhwadkhawkdhajwdhawhdaw=", 1623))
    // //     .Change("file.ln", CLink("").Change("file.txt"));

    // root.Change("file.txt", CFile("jhwadkhawkdhajwdhawhdaw=", 1623))
    //     .Change("file.ln", CLink("").Change("file.txt"))
    //     .Change("folder", CDirectory()
    //         .Change("fileA.txt", CFile("", 0).Change("skjdajdakljdljadkjwaljdlaw=", 1713))
    //         .Change("fileB.txt", CFile("kadwjkwajdwhoiwhduqwdqwuhd=", 71313))
    //         .Change("fileC.txt", CFile("aihdqhdqudqdiuwqhdquwdqhdi=", 8193))
    //     );

    // // cout << root.Get("file.txt").Size() << endl;
    // //root.print();

    // cout << root;


    CDirectory root;
    stringstream sout;

    root.Change("file.txt", CFile("jhwadkhawkdhajwdhawhdaw=", 1623))
        .Change("file.ln", CLink("").Change("file.txt"))
        .Change("folder", CDirectory()
            .Change("fileA.txt", CFile("", 0).Change("skjdajdakljdljadkjwaljdlaw=", 1713))
            .Change("fileB.txt", CFile("kadwjkwajdwhoiwhduqwdqwuhd=", 71313))
            .Change("fileC.txt", CFile("aihdqhdqudqdiuwqhdquwdqhdi=", 8193))
        );

    // cout << root << endl;
    // dynamic_pointer_cast <CDirectory&> ( root.Get("folder") ).Change("fileD.txt", CFile("aihdqhdqudqdiuwqhdquwdqhdi=", 81913));
    // root.Get("folder").Change("fileD.txt", CFile("aihdqhdqudqdiuwqhdquwdqhdi=", 81913));
    // cout << root << endl;

    sout.str( "" );
    sout << root;
    assert( sout.str() == 
        "9\tfile.ln -> file.txt\n"
        "1623\tfile.txt jhwadkhawkdhajwdhawhdaw=\n"
        "81246\tfolder/\n" );
    assert( root.Size() == 82899 );

    string filename = "folder";
    const CDirectory & inner = dynamic_cast<const CDirectory &>( root.Get( filename ) );

    sout.str( "" );
    sout << inner;
    assert( sout.str() ==
        "1713\tfileA.txt skjdajdakljdljadkjwaljdlaw=\n"
        "71313\tfileB.txt kadwjkwajdwhoiwhduqwdqwuhd=\n"
        "8193\tfileC.txt aihdqhdqudqdiuwqhdquwdqhdi=\n" );
    assert( inner.Size() == 81246 );

    return 0;
}
#endif /* __PROGTEST__ */
