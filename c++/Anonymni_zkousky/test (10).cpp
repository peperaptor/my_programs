#ifndef __PROGTEST__
#include <cassert>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>

// #include <iterator>

using namespace std;

class CResult
{
  	public: CResult ( const string & name, unsigned int   studentID, const string & test, int result )
		: m_Name ( name ), m_StudentID ( studentID ),m_Test ( test ),m_Result ( result )
    {

    }
    bool operator == ( const CResult& other ) const
    {
      return m_Name == other . m_Name && m_StudentID == other . m_StudentID && m_Test == other . m_Test && m_Result == other . m_Result;
    }
    string         m_Name;
    unsigned int   m_StudentID;
    string         m_Test;
    int            m_Result;
 };
#endif /* __PROGTEST__ */

class Student
{
public:
	string name;
	unsigned int id;
	Student()
	{
	}
	Student(string n, unsigned int i)
	{
		name = n;
		id = i;
	}
	friend bool operator<(const Student &left, const Student &right);
};
bool operator<(const Student &left, const Student &right)
{
	return left.id < right.id;
}
bool compareResById(const CResult &left, const CResult &right)
{
	return left.m_StudentID < right.m_StudentID;
}
bool compareResByName(const CResult &left, const CResult &right)
{
	return left.m_Name < right.m_Name;
}
bool compareResByResult(const CResult &left, const CResult &right)
{
	return left.m_Result > right.m_Result;
}

class CExam
{
private:
	map<string, Student> cardStudent;
	map<Student, set<string>> studentCard;

	map<string, vector< pair<Student, int>> > testResult;//получили оценку с теста
	map<Student, set<string>> studentTests;//все зарегестрированные на тест
public:
    static const int SORT_NONE   = 0;
    static const int SORT_ID     = 1;
    static const int SORT_NAME   = 2;
    static const int SORT_RESULT = 3;

    bool Load ( istream & cardMap )
    {
		map<string, Student> ncardStudent;
		map<Student, set<string>> nstudentCard;
		string str;
		while (getline(cardMap, str, '\n'))
		{
			std::string delimiter = ":";
			size_t pos = 0;
			string studentId;
			if((pos = str.find(delimiter)) != string::npos) 
			{
				studentId = str.substr(0, pos);
				// cout << " " << studentId;
				str.erase(0, pos + delimiter.length());
			}
			else
			{
				return false;
			}

			unsigned int stId;
			istringstream stream(studentId);
			stream >> stId;

			string studentName;
			if((pos = str.find(delimiter)) != string::npos) 
			{
				studentName = str.substr(0, pos);
				// cout << " " << studentName;
				str.erase(0, pos + delimiter.length());
			}
			else
			{
				return false;
			}

			Student newStudent(studentName, stId);

			if (studentCard.find(newStudent) != studentCard.end() 
				|| nstudentCard.find(newStudent) != nstudentCard.end())
			{
				return false;
			}

			set<string> newCards;

			delimiter = ",";
			while((pos = str.find(delimiter)) != string::npos) 
			{
				int i = 0;
				while (str[i] == ' ')
				{
					i++;
				}
				int posShift = 0;
				while (str[pos + posShift - 1] == ' ')
				{
					posShift -- ;
				}
				string isicId = str.substr(i, pos - i + posShift);
				str.erase(0, pos + delimiter.length());

				if (cardStudent.find(isicId) != cardStudent.end() 
					|| ncardStudent.find(isicId) != ncardStudent.end())
				{
					return false;
				}
				newCards.insert(isicId);
				ncardStudent[isicId] = newStudent;
			}
			int i = 0;
			while (str[i] == ' ')
			{
				i++;
			}
			int j = str.length() - 1;
			while (str[j] == ' ')
			{
				j--;
			}
			string lastId = str.substr(i, j - i + 1);

			if (cardStudent.find(lastId) != cardStudent.end() 
				|| ncardStudent.find(lastId) != ncardStudent.end())
			{
				return false;
			}
			newCards.insert(lastId);
			ncardStudent[lastId] = newStudent;

			nstudentCard[newStudent] = newCards;
		}
		cardStudent.insert(ncardStudent.begin(), ncardStudent.end());
		studentCard.insert(nstudentCard.begin(), nstudentCard.end());
		return true;
    }

    bool Register ( const string & cardID, const string & test )
	{
		if (cardStudent.count(cardID) == 0)
		{
			return false;
		}
		Student st = cardStudent.find(cardID)->second;
		if (studentTests.count(st) != 0 
			&& count(studentTests[st].begin(), studentTests[st].end(), test) != 0)//studentTests[st].count(test) != 0)
		{
			return false;
		}
		studentTests[st].insert(test);
		return true;
	}

    bool Assess ( unsigned int studentID, const string & test, int result )
	{
		auto it = studentCard.find(Student("", studentID));
		if (it == studentCard.end())
		{
			return false;
		}
		Student st = it->first;

		if (studentTests.count(st) == 0 
			|| count(studentTests[st].begin(), studentTests[st].end(), test) == 0 )
		{
			return false;
		}

		if (testResult.count(test) == 0)
		{
			testResult[test].push_back({st, result});
			return true;
		}
		
		
		auto last = testResult[test].end();
		for (auto current = testResult[test].begin(); 
					current != last; current ++)
		{
			if (current->first.id == st.id)
			{
				return false;
			}
		}
		testResult[test].push_back({st, result});
		return true;
	}	

    list<CResult> ListTest (const string & testName, int sortBy ) const
	{
		list<CResult> res;
		if (testResult.count(testName) == 0)
		{
			return res;
		}
		
		auto last = testResult.at(testName).end();
		for (auto current = testResult.at(testName).begin(); current != last; current ++)
		{
			res.push_back(CResult(current->first.name, current->first.id, testName, current->second));
		}
		if (sortBy == SORT_NONE)
		{
			return res;
		}
		if (sortBy == SORT_ID)
		{
			res.sort(compareResById);
			return res;
		}
		if (sortBy == SORT_NAME)
		{
			res.sort(compareResByName);
			return res;
		}
		if (sortBy == SORT_RESULT)
		{
			res.sort(compareResByResult);
			return res;
		}
		return res;
	}

    set<unsigned int> ListMissing (const string & testName ) const
	{
		set<unsigned int> res;
		
		set<unsigned int> registred;
		auto lastRegistred = studentTests.end();
		for (auto currentRegistred = studentTests.begin(); currentRegistred != lastRegistred; currentRegistred ++)
		{
			if (currentRegistred->second.count(testName) == 1)
			{
				registred.insert(currentRegistred->first.id);
			}
		}
		if (registred.empty())
		{
			return res;
		}
		if (testResult.count(testName) == 0)
		{
			return registred;
		}
		
		set<unsigned int> graded;
		auto last = testResult.at(testName).end();
		for (auto current = testResult.at(testName).begin(); current != last; current ++)
		{
			graded.insert(current->first.id);
		}

		//set_difference(graded.begin(), graded.end(), registred.begin(), registred.end(), inserter(res, res.begin()));
		auto end = registred.end();
		for (auto current = registred.begin(); current != end; current ++)
		{
			if (graded.count((*current)) == 0)
			{
				res.insert((*current));
			}
		}
		return res;
	}

	void print()
	{
		auto a = studentCard.begin();
		while(a != studentCard.end())
		{
			auto b = a->second.begin();
			cout << a->first.name << "(" << a->first.id << ")" <<endl;
			while(b != a->second.end())
			{
				cout << "	" << (*b) << endl;
				b++;
			}
			a++;
		}

		auto aa = studentTests.begin();
		while(aa != studentTests.end())
		{
			auto b = aa->second.begin();
			cout << aa->first.name << endl;
			while(b != aa->second.end())
			{
				cout << "	" << (*b) << endl;
				b++;
			}
			aa++;
		}

		auto aaa = testResult.begin();
		while(aaa != testResult.end())
		{
			auto b = aaa->second.begin();
			cout << aaa->first << endl;
			while(b != aaa->second.end())
			{
				cout << "	" << b->first.name <<  " " << b->first.id << " res= " << b->second << endl;
				b++;
			}
			aaa++;
		}
		// for (const auto& [card_id, stud] : cardStudent)
		// {

		// }
	}
};

#ifndef __PROGTEST__
int main ( void )
{
   istringstream iss;
  CExam         m;
//   assert ( m . ListMissing ( "PA2 - #3" ) == (set<unsigned int>{  }) );
// assert ( m . ListTest ( "PA2 - #1", CExam::SORT_NAME ) == (list<CResult>
//   {
    
//   } ) );
//   cout << 1;
  iss . clear ();
  iss . str ( "123456:Smith John:er34252456hjsd2451451, 1234151asdfe5123416, asdjklfhq3458235\n"
      "654321:Nowak Jane: 62wtsergtsdfg34\n"
      "456789:Nowak Jane: okjer834d34\n"
      "987:West Peter Thomas:sdswertcvsgncse\n" );
  assert ( m . Load ( iss ) );

  assert ( m . Register ( "62wtsergtsdfg34", "PA2 - #1" ) );
  assert ( m . Register ( "62wtsergtsdfg34", "PA2 - #2" ) );
  assert ( m . Register ( "er34252456hjsd2451451", "PA2 - #1" ) );
  assert ( m . Register ( "er34252456hjsd2451451", "PA2 - #3" ) );
  assert ( m . Register ( "sdswertcvsgncse", "PA2 - #1" ) );
  assert ( !m . Register ( "1234151asdfe5123416", "PA2 - #1" ) );
  assert ( !m . Register ( "aaaaaaaaaaaa", "PA2 - #1" ) );
  assert ( m . Assess ( 123456, "PA2 - #1", 50 ) );
  assert ( m . Assess ( 654321, "PA2 - #1", 30 ) );
  assert ( m . Assess ( 654321, "PA2 - #2", 40 ) );
  assert ( m . Assess ( 987, "PA2 - #1", 100 ) );
  assert ( !m . Assess ( 654321, "PA2 - #1", 35 ) );
  assert ( !m . Assess ( 654321, "PA2 - #3", 35 ) );
  assert ( !m . Assess ( 999999, "PA2 - #1", 35 ) );
  assert ( m . ListTest ( "PA2 - #1", CExam::SORT_RESULT ) == (list<CResult>
  {
    CResult ( "West Peter Thomas", 987, "PA2 - #1", 100 ),
    CResult ( "Smith John", 123456, "PA2 - #1", 50 ),
    CResult ( "Nowak Jane", 654321, "PA2 - #1", 30 )
  } ) );
  assert ( m . ListTest ( "PA2 - #1", CExam::SORT_NAME ) == (list<CResult>
  {
    CResult ( "Nowak Jane", 654321, "PA2 - #1", 30 ),
    CResult ( "Smith John", 123456, "PA2 - #1", 50 ),
    CResult ( "West Peter Thomas", 987, "PA2 - #1", 100 )
  } ) );
  assert ( m . ListTest ( "PA2 - #1", CExam::SORT_NONE ) == (list<CResult>
  {
    CResult ( "Smith John", 123456, "PA2 - #1", 50 ),
    CResult ( "Nowak Jane", 654321, "PA2 - #1", 30 ),
    CResult ( "West Peter Thomas", 987, "PA2 - #1", 100 )
  } ) );
  assert ( m . ListTest ( "PA2 - #1", CExam::SORT_ID ) == (list<CResult>
  {
    CResult ( "West Peter Thomas", 987, "PA2 - #1", 100 ),
    CResult ( "Smith John", 123456, "PA2 - #1", 50 ),
    CResult ( "Nowak Jane", 654321, "PA2 - #1", 30 )
  } ) );

//   m.print();
  assert ( m . ListMissing ( "PA2 - #3" ) == (set<unsigned int>{ 123456 }) );
  iss . clear ();
  iss . str ( "888:Watson Joe:25234sdfgwer52, 234523uio, asdf234235we, 234234234\n" );
  assert ( m . Load ( iss ) );

  assert ( m . Register ( "234523uio", "PA2 - #1" ) );
  assert ( m . Assess ( 888, "PA2 - #1", 75 ) );
  iss . clear ();
  iss . str ( "555:Gates Bill:ui2345234sdf\n"
      "888:Watson Joe:2345234634\n" );
  assert ( !m . Load ( iss ) );

  assert ( !m . Register ( "ui2345234sdf", "PA2 - #1" ) );
  iss . clear ();
  iss . str ( "555:Gates Bill:ui2345234sdf\n"
      "666:Watson Thomas:okjer834d34\n" );
  assert ( !m . Load ( iss ) );

  assert ( !m . Register ( "ui2345234sdf", "PA2 - #3" ) );
  iss . clear ();
  iss . str ( "555:Gates Bill:ui2345234sdf\n"
      "666:Watson Thomas:jer834d3sdf4\n" );
  assert ( m . Load ( iss ) );

  assert ( m . Register ( "ui2345234sdf", "PA2 - #3" ) );
  assert ( m . ListMissing ( "PA2 - #3" ) == (set<unsigned int>{ 555, 123456 }) );
  return 0;
}
#endif /* __PROGTEST__ */
