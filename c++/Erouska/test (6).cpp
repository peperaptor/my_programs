#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

class CTimeStamp
{
public:
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    
    CTimeStamp()
    {
    }
    CTimeStamp(int nyear, int nmonth, int nday, int nhour, int nmin, int nsec)
    {
        year = nyear;
        month = nmonth;
        day = nday;
        hour = nhour;
        min = nmin;
        sec = nsec;
    }

    void print() const
    {
        cout << year << "." << month  << "." << day  << "." << hour << "." << min  << "." << sec  << "\n";
    }

    friend bool operator== (const CTimeStamp &date1, const CTimeStamp &date2);
    friend bool operator< (const CTimeStamp &date1, const CTimeStamp &date2);
    
};

bool operator== (const CTimeStamp &date1, const CTimeStamp &date2)
{
    long long fdate = date1.year * 10000000000 + date1.month * 100000000 + date1.day * 1000000 + date1.hour * 10000 + date1.min * 100 + date1.sec;
    long long  sdate = date2.year * 10000000000 + date2.month * 100000000 + date2.day * 1000000 + date2.hour * 10000 + date2.min * 100 + date2.sec;
    if (fdate == sdate)
    {
        return true;
    }
    return false;
}

bool operator< (const CTimeStamp &date1, const CTimeStamp &date2)
{
    long long fdate = date1.year * 10000000000 + date1.month * 100000000 + date1.day * 1000000 + date1.hour * 10000 + date1.min * 100 + date1.sec;
    long long  sdate = date2.year * 10000000000 + date2.month * 100000000 + date2.day * 1000000 + date2.hour * 10000 + date2.min * 100 + date2.sec;
    if (fdate < sdate)
    {
        return true;
    }
    return false;
}

class CContact
{
public:
    CTimeStamp contackDate;
    int user1PhoneNumber;
    int user2PhoneNumber;
    CContact()
    {
    }
    CContact(CTimeStamp date, int us1PhoneNumber, int us2PhoneNumber)
    {
        contackDate = date;
        user1PhoneNumber = us1PhoneNumber;
        user2PhoneNumber = us2PhoneNumber;
    }

    void print() const
    {
        contackDate.print();
        cout << "ph1: " << user1PhoneNumber << " ph2: " << user2PhoneNumber << "\n";
    }

    int contactedUserNumber(int phoneNumb) const
    {
        if (phoneNumb == user1PhoneNumber)
        {
            return user2PhoneNumber;
        }
        return user1PhoneNumber;
    }
    friend bool operator== (const CContact &f, const CContact &s);

};
bool operator== (const CContact &f, const CContact &s)
{
    if ((f.contackDate == s.contackDate) && 
        (((f.user1PhoneNumber == s.user1PhoneNumber) && (f.user2PhoneNumber == s.user2PhoneNumber)) 
        || ((f.user2PhoneNumber == s.user1PhoneNumber) && (f.user1PhoneNumber == s.user2PhoneNumber))))
    {
        return true;
    }
    return false;
}

class CEFaceMask
{
private:
    vector <CContact> contacts;
    bool isExist(CContact newContact) const
    {
        bool res = false;
        for (size_t i = 0; i < contacts.size(); i++)
        {
            if (contacts.at(i) == newContact)
            {
                res = true;
                return res;
            }
        }
        return res;
    }
public:
    CEFaceMask(){}
    CEFaceMask & addContact(CContact newContact)
    {
        if (!isExist(newContact))
        {
            contacts.push_back(newContact);
        }
        return *this;
    }

    vector<int> listContacts(int userNumber) const
    {
        vector<int> res;
        for (size_t i = 0; i < contacts.size(); i++)
        {
            if (((contacts.at(i).user1PhoneNumber == userNumber) || (contacts.at(i).user2PhoneNumber == userNumber))
            && (contacts.at(i).user1PhoneNumber != contacts.at(i).user2PhoneNumber) )
            {
                if((find(res.begin(), res.end(), contacts.at(i).contactedUserNumber(userNumber)) == res.end())) 
                {
                    res.push_back(contacts.at(i).contactedUserNumber(userNumber));
                    // cout << "userNumber: " << userNumber << "\n";
                }
            }
        }
        return res;
    };
    vector<int> listContacts(int userNumber, CTimeStamp start, CTimeStamp end) const
    {
        vector<int> res;
        for (size_t i = 0; i < contacts.size(); i++)
        {
            if (((contacts.at(i).user1PhoneNumber == userNumber) || (contacts.at(i).user2PhoneNumber == userNumber))
            && (contacts.at(i).user1PhoneNumber != contacts.at(i).user2PhoneNumber) )
            {
                if ((!(contacts.at(i).contackDate < start)) 
                && ((contacts.at(i).contackDate < end) || (contacts.at(i).contackDate == end))

                && (find(res.begin(), res.end(), contacts.at(i).contactedUserNumber(userNumber)) == res.end()))
                {
                    res.push_back(contacts.at(i).contactedUserNumber(userNumber));
                    // contacts.at(i).print();
                    // cout << "userNumber: " << userNumber << "\n";
                }
            }
        }
        return res;
    };
};

#ifndef __PROGTEST__
int main ()
{
  CEFaceMask test;

  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 10, 12, 40, 10 ), 123456789, 999888777 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 12, 12, 40, 10 ), 123456789, 111222333 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 5, 15, 30, 28 ), 999888777, 555000222 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 21, 18, 0, 0 ), 123456789, 999888777 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), 123456789, 456456456 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 1, 0, 0, 0 ), 123456789, 123456789 ) );
  assert ( test . listContacts ( 123456789 ) == (vector<int> {999888777, 111222333, 456456456}) );
  assert ( test . listContacts ( 999888777 ) == (vector<int> {123456789, 555000222}) );
  assert ( test . listContacts ( 191919191 ) == (vector<int> {}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), CTimeStamp ( 2021, 2, 21, 18, 0, 0 ) ) == (vector<int> {999888777, 111222333, 456456456}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 1 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {999888777, 111222333}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 10, 12, 41, 9 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {111222333}) );
  return 0;
}
#endif /* __PROGTEST__ */
