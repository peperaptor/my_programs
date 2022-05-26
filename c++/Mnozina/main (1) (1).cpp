#ifndef __PROGTEST__
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

// #include <cassert>


class CLinkedSetTester;
#endif /* __PROGTEST__ */

class CLinkedSet
{
private:

    struct CNode
    {
    private :
        char * _value = nullptr;

    public:
        CNode * m_Next = nullptr;

        const char * Value() const
        {
            if (_value != nullptr)
            {
                return _value;
            }
            return "";
        }

        void setValue(const char *nv)
        {
            if (nv != nullptr)
            {
                size_t size = strlen(nv) + 1;
                _value = new char[size];
                strcpy(_value, nv);
            }
        }

        void delValue()
        {
            if (_value != nullptr)
            {
                delete[] _value;
                _value = nullptr;
            }
        }

    };

    CNode * m_Begin = nullptr;

    void deleteThis()
    {
    	CNode *nodeToDel = m_Begin;
    	while (nodeToDel != nullptr)
    	{
    		const char *valToDel = nodeToDel->Value();
    		nodeToDel = nodeToDel->m_Next;
    		Remove(valToDel);
    	}
//        CNode *nodeToDel = m_Begin;
//        while (nodeToDel != nullptr)
//        {
//            m_Begin = nodeToDel->m_Next;
//            //cout << nodeToDel->Value() << "\n";
//            nodeToDel->delValue();
//            delete nodeToDel;
//            nodeToDel = m_Begin;
//        }
    }

public:
    CLinkedSet()
    {
        m_Begin = nullptr;
    }

    // void deleteandWrite()
    // {
    //     deleteThis();
    //     print();
    //     cout << "deleted\n";
    // }

    CLinkedSet(const CLinkedSet& oldClist)
    {
    	m_Begin = nullptr;
		CNode *oldcurrNode = oldClist.m_Begin;
		while (oldcurrNode != nullptr)
		{
			Insert(oldcurrNode->Value());
			oldcurrNode = oldcurrNode->m_Next;
//			cout << "After insert\n";
//			print();
		}
//            m_Begin = new CNode;
//            CNode *oldcurrNode = oldClist.m_Begin;
//            CNode *newcurrNode = m_Begin;
//
//            newcurrNode->setValue(oldcurrNode->Value());
//            oldcurrNode = oldcurrNode->m_Next;
//
//            while (oldcurrNode != nullptr)
//            {
//                newcurrNode->m_Next = new CNode;
//                newcurrNode = newcurrNode->m_Next;
//                newcurrNode->setValue(oldcurrNode->Value());
//                oldcurrNode = oldcurrNode->m_Next;
//            }
//            newcurrNode->m_Next = nullptr;
    }

    void print()
    {
        CNode *currNode = m_Begin;
        while (currNode != nullptr)
        {
            cout << currNode->Value();
            cout << " pointer " << endl;;
            currNode = currNode->m_Next;
        }
    }

    ~CLinkedSet()
    {
        deleteThis();
    }

    bool Insert(const char *value)
    {
        if (Contains(value))
        {
            return false;
        }

        if (m_Begin == nullptr)
        {
            m_Begin = new CNode;
            m_Begin->m_Next = nullptr;
            m_Begin->setValue(value);
            return true;
        }

        if (strcmp(m_Begin->Value(), value) > 0)
        {
        	CNode *node = new CNode;
        	node->setValue(value);
			node->m_Next = m_Begin;
			m_Begin = node;
			node = nullptr;
			return true;
        }

        CNode *currNode = m_Begin;
        while (currNode->m_Next != nullptr && strcmp(currNode->m_Next->Value(), value) < 0)
        {
        	currNode = currNode->m_Next;
        }
        CNode *node = new CNode;
		node->setValue(value);
		node->m_Next = currNode->m_Next;
		currNode->m_Next = node;
		node = nullptr;
		return true;
    }

    bool Remove(const char * value)
    {
    	// making sure element is in the list
    	if (!Contains(value)) {
    		return false;
    	}

        if (strcmp(m_Begin->Value(), value) == 0)
        {
            CNode * nodeToDel = m_Begin;
            m_Begin = m_Begin->m_Next;
            nodeToDel->delValue();
            delete nodeToDel;
            nodeToDel = nullptr;
            return true;
        }

        CNode *currNode = m_Begin;
		while (strcmp(currNode->m_Next->Value(), value) != 0)
		{
			currNode = currNode->m_Next;
		}
		CNode * nodeToDel = currNode->m_Next;
		currNode->m_Next = currNode->m_Next->m_Next;
		nodeToDel->delValue();
		delete nodeToDel;
		nodeToDel = nullptr;
		return true;
    }

    bool Empty() const
    {
        return m_Begin == nullptr;
    }

    size_t Size() const
    {
        size_t res = 0;
        CNode *currNode = m_Begin;
        while (currNode != nullptr)
        {
            res++;
            currNode = currNode->m_Next;
        }
        return res;
    }

    bool Contains(const char *value ) const
    {
        if (m_Begin == nullptr)
        {
            return false;
        }

        CNode *currNode = m_Begin;
        while (currNode != nullptr)
        {
            if (strcmp(currNode->Value(), value) == 0)
            {
                return true;
            }
            currNode = currNode->m_Next;
        }
        return false;
    }

    CLinkedSet operator= (CLinkedSet rhs)
    {
    	swap(m_Begin, rhs.m_Begin);
//        deleteThis();
//        if (rhs.m_Begin != nullptr)
//        {
//            m_Begin = new CNode;
//            CNode *oldcurrNode = rhs.m_Begin;
//            CNode *newcurrNode = m_Begin;
//
//            newcurrNode->setValue(oldcurrNode->Value());
//            oldcurrNode = oldcurrNode->m_Next;
//
//            while (oldcurrNode != nullptr)
//            {
//                newcurrNode->m_Next = new CNode;
//                newcurrNode = newcurrNode->m_Next;
//                newcurrNode->setValue(oldcurrNode->Value());
//                oldcurrNode = oldcurrNode->m_Next;
//            }
//            newcurrNode->m_Next = nullptr;
//        }
        return *this;
    }
    friend class ::CLinkedSetTester;
};



#ifndef __PROGTEST__
#include <cassert>

struct CLinkedSetTester
{
    static void test0()
    {
        CLinkedSet x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        assert( !x0 . Empty() );
    }

    static void test1()
    {
        CLinkedSet x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        CLinkedSet x1 ( x0 );
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );
    }

    static void test2()
    {
        CLinkedSet x0;
        CLinkedSet x1;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
//        cout << "After insert" << endl;
//        x0.print();
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
//        cout << "After remove" << endl;
//        x0.print();
        x1 = x0;
//        cout << "After assign" << endl;
//        x1.print();
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );
    }

};

int main ()
{
//    CLinkedSet x0;
//    x0 . Insert( "ads" );
//    x0 . Insert( "Pavlik Ales" );
//    x0 . Insert( "Dusek Zikmund" );
//    x0 . Insert( "gdfh" );
//    x0 . Insert( "dfg" );
//    x0 . Insert( "dfg" );
//    x0 . Insert( "adsdfs" );
//    x0 . Insert( "asdfds" );
//    x0 . Insert( "aczds" );
//    x0 . Insert( "azxcds" );
//    x0 . Insert( "avxds" );
//    x0 . Insert( "avxcds" );
//    x0 . Insert( "abds" );
//    x0 . Insert( "ancds" );
//    x0 . Insert( "acbvds" );
//    x0 . Insert( "adxsdcvs" );
//    x0 . Insert( "adxvcs" );
//    x0 . Insert( "abcds" );
//    x0 . Insert( "xcvxvc" );
//    x0 . Insert( "xcv" );
//    x0 . Insert( "sdf" );
//    x0 . Insert( "fgdsh" );
//    x0 . Insert( "sdf" );
//    x0 . Insert( "agffag" );
//    x0 . Insert( "adFDs" );
//    x0 . Insert( "BBZCVBZNM" );
//    x0 . Insert( "SDF" );
//    x0 . Insert( "XCV" );
//    x0 . Insert( "gswer" );
//    x0 . Insert( ",ds" );
//    x0 . Insert( "bvxzcg" );
//    x0 . Insert( "asgf" );
//    x0 . Insert( "hsg" );
//    x0 . Insert( "shgf" );
//    x0 . Insert( "bvcxcbxcvb" );
//    x0 . Insert( "gdsafg" );
//    x0 . Insert( "aahfdfhgerts" );
//    x0 . Insert( "dfgzcnbcb" );
//    x0 . Insert( "acxvds" );
//    x0 . Insert( "azxbvcds" );
//    x0 . Insert( "adsvdsfs" );
//    x0 . Insert( "sdfads" );
//    x0 . Insert( "adssghfvcx" );
//    x0 . Insert( "sdgfads" );
//    x0 . Insert( "adshgadb" );
//    x0 . Insert( "adssf" );
//    x0 . Insert( "adssfd" );
//    x0 . Insert( "adsdfdfdsfs" );
//    CLinkedSet x1(x0);
    // x0.Insert("asdads asdad");

//    x0.print();
    // cout << 1 << endl;

    // CLinkedSet x1(x0);
    // x0.Remove("Dusek Zikmund");
    // x0.print();
    // cout << "****************\n";
    // x1.print();


    // CLinkedSet x0;

    // assert( x0 . Insert( "Jerabek Michal" ) );
    // assert( x0 . Insert( "Pavlik Ales" ) );
    // assert( x0 . Insert( "Dusek Zikmund" ) );
    // assert( x0 . Size() == 3 );
    // assert( x0 . Contains( "Dusek Zikmund" ) );
    // assert( !x0 . Contains( "Pavlik Jan" ) );
    // assert( x0 . Insert( "Vodickova Saskie" ) );
    // assert( x0 . Insert( "Kadlecova Kvetslava" ) );

    // cout << "****************\n";
    // x0.print();
    // assert( x0 . Remove( "Jerabek Michal" ) );
    // assert( x0 . Remove( "Pavlik Ales" ) );
    // assert( x0 . Remove( "Dusek Zikmund" ) );
    // assert( x0 . Remove( "Vodickova Saskie" ) );
    // assert( x0 . Remove( "Kadlecova Kvetslava" ) );
    // assert( !x0 . Contains( "Dusek Zikmund" ) );
    // cout << "****************\n";
    // x0.print();
    // CLinkedSet x1(x0);
    // assert( !x1 . Contains( "Vodickova Saskie" ) );
    // cout << "****************\n";
    // x1.print();
    // cout << "****************\n";


    // CLinkedSet a;
    // a.Insert("aaa11");
    // a.print();
    // cout << "****************\n";
    // a.Insert("bbb11");
    // a.print();
    // cout << "****************\n";
    // a.Insert("11111");
    // a.Insert("22222");
    // a.Insert("55555");
    // a.Insert("33333");
    // a.Insert("aaaaa");
    // a.print();
    // cout << "****************\n";
    // CLinkedSet b;
    // b = a;
    // b.print();
    // cout << "***********************\n";
    // a.Insert("aaaaaaaa");
    // a.print();


    CLinkedSetTester::test0();
    CLinkedSetTester::test1();
    CLinkedSetTester::test2();
    cout << "Finished\n";

    return 0;
}
#endif /* __PROGTEST__ */


