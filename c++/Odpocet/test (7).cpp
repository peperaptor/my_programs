#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

class CTimeTester;
#endif /* __PROGTEST__ */

class CTime
{
private:
    int m_Hour;
    int m_Minute;
    int m_Second;
    
    void setHours(int m_RealSeconds)
    {
        m_Hour = (m_RealSeconds / 3600) % 24;
    }

    void setMinuts(int m_RealSeconds)
    {
        m_Minute = (m_RealSeconds / 60) % 60;
        setHours(m_RealSeconds);
    }

public:
    CTime()
    {
        m_Hour = 0;
        m_Minute = 0;
        m_Second = 0;
    }
    CTime(int hour, int minut)
    {
        m_Hour = 0;
        m_Minute = 0;
        m_Second = 0;
        if ((hour < 0) || (minut < 0)||
            (hour > 23) || (minut > 59))
        {
            throw invalid_argument("");
        }
        addSeconds(minut * 60 + 3600 * hour);
    }
    CTime(int hour, int minut, int second)
    {
        m_Hour = 0;
        m_Minute = 0;
        m_Second = 0;
        if ((hour < 0) || (minut < 0) || (second < 0) ||
            (hour > 23) || (minut > 59) || (second > 59))
        {
            throw invalid_argument("");
        }
        addSeconds(second + 60 * minut + 3600 * hour);
    }
    ~CTime()
    {

    }

    void addSeconds(int s)
    {
        int m_RealSeconds = getAsSeconds();
        m_RealSeconds += s;
        if (m_RealSeconds < 0)
        {
            m_RealSeconds = (3600 * 24) + (m_RealSeconds % (3600 * 24));
        }
        m_Second = m_RealSeconds % 60;
        setMinuts(m_RealSeconds);
    }

    void setSeconds(int s, int m, int h)
    {
        m_Hour = 0;
        m_Minute = 0;
        m_Second = 0;
        addSeconds(s + 60 * m + 3600 * h);
    }

    const int getAsSeconds()
    {
        return m_Second + m_Minute * 60 + m_Hour * 3600;
    }

    friend CTime operator+ (const CTime &left, const int &right);
    friend CTime operator+ (const int &right, const CTime &left);
    friend CTime& operator+=(CTime& left, const int & right);

    friend CTime operator- (const CTime &left, const int &right);
    friend CTime operator- (const int &right, const CTime &left);
    friend CTime& operator-=(CTime& left, const int & right);

    
    friend int operator- (const CTime &left, const CTime  &right);

    friend const CTime operator++(CTime& a, int);

    friend const CTime& operator++(CTime& i);
    friend const CTime operator++(CTime& i, int);

    friend const CTime& operator--(CTime& i);
    friend const CTime operator--(CTime& i, int);

    friend bool operator< (const CTime &l, const CTime &r);
    friend bool operator<= (const CTime &l, const CTime &r);
    friend bool operator> (const CTime &l, const CTime &r);
    friend bool operator>= (const CTime &l, const CTime &r);
    friend bool operator== (const CTime &l, const CTime &r);
    friend bool operator!= (const CTime &l, const CTime &r);

    friend ostream& operator<< (ostream &out, const CTime &time);
    friend ostream& operator>> (ostream &in, CTime &time);

    friend class ::CTimeTester;
};

CTime operator+ (CTime const &left,  int const &right)
{
    CTime tmp;
    tmp.setSeconds(left.m_Second, left.m_Minute, left.m_Hour);
    tmp.addSeconds(right);
    return tmp;
}
CTime operator+ (int const &right, CTime const &left)
{
    CTime tmp;
    tmp.setSeconds(left.m_Second, left.m_Minute, left.m_Hour);
    tmp.addSeconds(right);
    return tmp;
}
CTime& operator+=(CTime& left, const int & right)
{
    left.addSeconds(right);
    return left;
}

CTime operator- (const CTime &left,  int const &right)
{
    CTime tmp;
    tmp.setSeconds(left.m_Second, left.m_Minute, left.m_Hour);
    tmp.addSeconds(- right);
    return tmp;
}
CTime operator- (int const &right, const CTime &left)
{
    CTime tmp;
    tmp.setSeconds(left.m_Second, left.m_Minute, left.m_Hour);
    tmp.addSeconds(- right);
    return tmp;
}
CTime& operator-=(CTime& left, const int & right)
{
    left.addSeconds(- right);
    return left;
}

int operator- (const CTime &left,  const CTime &right)
{
    CTime ltmp {left.m_Hour, left.m_Minute, left.m_Second};
    CTime rtmp {right.m_Hour, right.m_Minute, right.m_Second};
    int a = ltmp.getAsSeconds() - rtmp.getAsSeconds(), b = rtmp.getAsSeconds() - ltmp.getAsSeconds();
    if (a < 0)
    {
        a = 3600*24 + a;
    }
    if (b < 0)
    {
        b = 3600*24 + b;
    }
    if (a < b)
    {
        return a;
    }
    return b;
}

const CTime& operator++(CTime& i) 
{
    i.addSeconds(1);
    return i;
}
const CTime operator++(CTime& i, int) 
{
    CTime oldValue(i.m_Hour, i.m_Minute, i.m_Second);
    i.addSeconds(1);
    return oldValue;
}

const CTime& operator--(CTime& i) 
{
    i.addSeconds(-1);
    return i;
}
const CTime operator--(CTime& i, int) 
{
    CTime oldValue(i.m_Hour, i.m_Minute, i.m_Second);
    i.addSeconds(-1);
    return oldValue;
}

bool operator< (const CTime &l, const CTime &r)
{
    CTime ltmp{l.m_Hour, l.m_Minute, l.m_Second};
    CTime rtmp{r.m_Hour, r.m_Minute, r.m_Second};
    if (ltmp.getAsSeconds() < rtmp.getAsSeconds())
    {
        return true;
    }
    return false;
}
bool operator> (const CTime &l, const CTime &r)
{
    CTime ltmp{l.m_Hour, l.m_Minute, l.m_Second};
    CTime rtmp{r.m_Hour, r.m_Minute, r.m_Second};
    if (ltmp.getAsSeconds() > rtmp.getAsSeconds())
    {
        return true;
    }
    return false;
}
bool operator<= (const CTime &l, const CTime &r)
{
    return (!(l > r));
}
bool operator>= (const CTime &l, const CTime &r)
{
    return (!(l < r));
}
bool operator== (const CTime &l, const CTime &r)
{
    return ((l <= r) and (l >= r));
}
bool operator!= (const CTime &l, const CTime &r)
{
    return (!(r == l));
}

ostream& operator<< (ostream &out, const CTime &time)
{
    out << 
    setfill(' ') << setw(2) << time.m_Hour << ":" << 
    setfill('0') << setw(2) << time.m_Minute << ":" << 
    setfill('0') << setw(2) << time.m_Second;
    return out;
}

istream& operator>> (istream &in, CTime &time)
{
    int h, m, s;
    char a, b;

    in >> skipws >> h >> noskipws >> a >> noskipws >> m  >> noskipws >> b >> noskipws >> s;
    if (((a == ':') && (b == ':'))
        && ((h >= 0) && (m >= 0) && (s >= 0))
            && ((h < 24) && (m < 60) && (s < 60)))
    {
        time.setSeconds(0,0,0);
        time.addSeconds(s + (60 * m) + (3600 * h));
    }
    else
    {
        in.setstate(ios::failbit);
    }
    return in;
}

#ifndef __PROGTEST__
struct CTimeTester
{
    static bool test ( const CTime & time, int hour, int minute, int second )
    {
        return time.m_Hour == hour 
            && time.m_Minute == minute
            && time.m_Second == second;
    }
};

#include <cassert>
#include <sstream>

int main ()
{
    
    CTime ab;
    // istringstream asd { "13:30 :00" };
    // assert( static_cast<bool>( asd >> ab ) );
    while(true)
    {
        cin >> ab;
        cout << ab;
    }

    CTime a { 12, 30 };
    assert( CTimeTester::test( a, 12, 30, 0 ) );

    CTime b;
    std::istringstream input { "13:30:00" };
    assert( static_cast<bool>( input >> b ) );
    assert( CTimeTester::test( b, 13, 30, 0 ) );

    assert( b - a == 3600 );


    assert( CTimeTester::test( a + 60, 12, 31, 0 ) );

    assert( CTimeTester::test( a - 60, 12, 29, 0 ) );

    assert( a < b );
    assert( a <= b );
    assert( a != b );
    assert( !( a > b ) );
    assert( !( a >= b ) );
    assert( !( a == b ) );

    while ( ++a != b );
    assert( a == b );

    std::ostringstream output;
    assert( static_cast<bool>( output << a ) );
    assert( output.str() == "13:30:00" );

    assert( a++ == b++ );
    assert( a == b );

    assert( --a == --b );
    assert( a == b );

    assert( a-- == b-- );
    assert( a == b );

    return 0;
}
#endif /* __PROGTEST__ */
