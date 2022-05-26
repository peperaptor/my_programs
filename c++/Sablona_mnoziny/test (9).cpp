#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <algorithm>
#include <functional>

#include <stdexcept>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdint>
#include <cctype>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

template <class T>

class CSet
{
private:
    struct CNode
    {
    private :
        T _value;
        
    public:
        CNode * m_Next = nullptr;

        
        // CNode(CNode * n):_value(n->_value), m_Next(n->m_Next)
        // {
        //     // _value = n->_value;
        //     // m_Next = n->m_Next;
        // };
        CNode(T _val, CNode * next): _value(_val), m_Next(next)
        {
            // _value = val;
            // m_Next = next;
        };
        // CNode()
        // {

        // };
        const T Value() const
        {
            return _value;
        }

        void setValue(const T &nv)
        {
            _value = T(nv);
        }
    };
    CNode * m_Begin = nullptr;

    // size_t length = 0;
    // size_t size = 100;
    // T *data = nullptr;

    // int findAdress(const T &val) const
    // {
    //     if (length == 0)
    //     {
    //         return 0;
    //     }
    //     if (data[length - 1] < val)
    //     {
    //         return length;
    //     }
    //     int left = 0, right = length - 1;
    //     int mid = 0;
    //     while (left < right)
    //     {
    //         // cout << "left= " << left << " right= " << right << " mid= " << mid << " val= " << val << endl;
    //         mid = (left + right) / 2;
    //         if (val < data[mid])
    //         {
    //             right = mid;   
    //         }   
    //         else if (data[mid] < val)//(val > data[mid]) 
    //         {
    //             left = mid + 1;  
    //         }  
    //         else  
    //         {         
    //             return mid; 
    //         }
    //     }
    //     return right;
    // }
    // void increaseSize()
    // {
    //     size = size * 2;
    //     T *tmp = new T [size];
    //     for (size_t i = 0; i < length; i++)//заменить на копи тут и в других местах
    //     {
    //         tmp[i] = data[i];
    //     }
    //     delete [] data;
    //     data = tmp;
    // }

    void deleteThis()
    {
    	CNode *nodeToDel = m_Begin;
    	while (nodeToDel != nullptr)
    	{
    		const T valToDel = nodeToDel->Value();
    		nodeToDel = nodeToDel->m_Next;
    		Remove(valToDel);
    	}
    }

public:
    CSet()
    {
        m_Begin = nullptr;
    }
    CSet(const CSet<T> &src)
    {
        m_Begin = nullptr;
		CNode *oldcurrNode = src.m_Begin;
		while (oldcurrNode != nullptr)
		{
			Insert(oldcurrNode->Value());
			oldcurrNode = oldcurrNode->m_Next;
		}
    }

    ~CSet()
    {
        // delete[] data;
        deleteThis();
    }
    bool Contains(const T &value) const
    {
        if (m_Begin == nullptr)
        {
            return false;
        }

        CNode *currNode = m_Begin;
        while (currNode != nullptr)
        {
            if (!(currNode->Value() < value) && !(value < currNode->Value()))
            {
                return true;
            }
            currNode = currNode->m_Next;
        }
        return false;
    }

    // bool Contains(const T &val) const
    // {
    //     size_t adr = findAdress(val);
    //     if (!(data[adr] < val) && !(val < data[adr]))
    //     {
    //         return true;
    //     }
    //     return false;
    // }

    bool Insert(const T &value)
    {
        if (Contains(value))
        {
            return false;
        }

        if (m_Begin == nullptr)
        {
            m_Begin = new CNode(value, nullptr);
            // m_Begin->m_Next = nullptr;
            // m_Begin->setValue(value);
            return true;
        }

        if (value < m_Begin->Value())
        {
        	CNode *node = new CNode(value, m_Begin);
        	// node->setValue(value);
			// node->m_Next = m_Begin;
			m_Begin = node;
			node = nullptr;
			return true;
        }

        CNode *currNode = m_Begin;
        while (currNode->m_Next != nullptr && currNode->m_Next->Value() < value)
        {
        	currNode = currNode->m_Next;
        }
        CNode *node = new CNode(value, currNode->m_Next);
		// node->setValue(value);
		// node->m_Next = currNode->m_Next;
		currNode->m_Next = node;
		node = nullptr;
		return true;
    }

    // bool Insert(const T &val)
    // {
    //     if (length == 0)
    //     {
    //         data = new T[size];
    //         data[0] = val;
    //         length++;
    //         return true;
    //     }
    //     if (Contains(val))
    //     {
    //         return false;
    //     }
    //     if (length == size)
    //     {
    //         increaseSize();
    //     }
    //     size_t adr = findAdress(val);
    //     for (size_t i = length; i > adr; i--)
    //     {
    //         data[i] = data[i - 1];
    //     } 
    //     length++;
    //     data[adr] = val;
    //     return true;
    // }
    
    bool Remove(const T &value)
    {
    	if (!Contains(value)) {
    		return false;
    	}
        if (!(m_Begin->Value() < value) && !(value < m_Begin->Value()))
        {
            CNode * nodeToDel = m_Begin;
            m_Begin = m_Begin->m_Next;
            delete nodeToDel;
            nodeToDel = nullptr;
            return true;
        }

        CNode *currNode = m_Begin;
		while ((currNode->m_Next->Value() < value) || (value < currNode->m_Next->Value()))
		{
			currNode = currNode->m_Next;
		}
        CNode * nodeToDel = currNode->m_Next;
		currNode->m_Next = currNode->m_Next->m_Next;
		delete nodeToDel;
		return true;
    }

    // bool Remove(const T &val)
    // {
    //     if (!Contains(val))
    //     {
    //         return false;
    //     }
    //     size_t adr = findAdress(val);
    //     length--;
    //     for (size_t i = adr; i < length; i++)
    //     {
    //         data[i] = data[i + 1];
    //     }
    //     return true;
    // }

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


    CSet operator= (CSet rhs)
    {
    	swap(m_Begin, rhs.m_Begin);
        return *this;
    }

    // CSet& operator = (const CSet &right)
    // {
    //     CSet newCset(right);
    //     swap(data, newCset.data);
    //     length = newCset.length;
    //     size = newCset.length;
    //     return *this;
    // }

    // void print()
    // {
    //     for (size_t i = 0; i < length; i++)
    //     {
    //         cout << data[i] << endl;
    //     }
    // }
    void print()
    {
        CNode *currNode = m_Begin;
        while (currNode != nullptr)
        {
            cout << currNode->Value() << endl;
            currNode = currNode->m_Next;
        }
    }
};


#ifndef __PROGTEST__
#include <cassert>

struct CSetTester
{
    static void test0()
    {
        CSet<string> x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );

        // x0.print();
        // cout << endl;
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );

        // x0.print();
        // assert( !x0 . Contains( "Jerabek Michal" ) );
        
    }

    static void test1()
    {
        CSet<string> x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        CSet<string> x1 ( x0 );
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
        CSet<string> x0;
        CSet<string> x1;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        x1 = x0;
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );

    }

    static void test4()
    {
        CSet<int> x0;
        assert( x0 . Insert( 4 ) );
        assert( x0 . Insert( 8 ) );
        assert( x0 . Insert( 1 ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( 4 ) );
        assert( !x0 . Contains( 5 ) );
        assert( !x0 . Remove( 5 ) );
        assert( x0 . Remove( 4 ) );
    }

};

int main ()
{
    // CSet<int> a;
    // a.Insert(6);
    // a.Insert(3);
    // // a.print();
    // // cout << "\n" << a.f(-1) << endl;

    // CSet<int> x0;
    // // assert( x0 . Insert( 4 ) );
    // // assert( x0 . Insert( 8 ) );
    // // assert( x0 . Insert( 1 ) );
    // // x0.print();
    // x0 = a;

    // CSet<int> x1(x0);
    // x0.Insert(100);
    // x1.print();

    CSetTester::test0();
    CSetTester::test1();
    CSetTester::test2();
    CSetTester::test4();
    cout << 1;
    return 0;
}
#endif /* __PROGTEST__ */
