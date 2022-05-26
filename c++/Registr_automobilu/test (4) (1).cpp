#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST__ */


struct personCar// a structure that stores the name and surname of a person, his car number
{
    string name;
    string surname;
    string RZ;
};


bool cmpNameSurname(const personCar &u1, const personCar &u2)//comparator that compares structure objects based on last name and first name
{
	if (u1.surname == u2.surname)
	{
		return u1.name < u2.name;
	}
	return u1.surname < u2.surname;
}

bool cmpRZ(const personCar &u1, const personCar &u2)//comparator comparing structure objects based on car number
{
    return u1.RZ < u2.RZ;
}

class CCarList
{
public:
	CCarList( vector<personCar>::const_iterator curr, vector<personCar>::const_iterator end)// constructor that fills the iterators
	{
		currentIt = curr;
		endIt = end;
	}
	const string & RZ ( void ) const
	{
		return (*currentIt).RZ;
	}
	bool AtEnd	 ( void ) const
	{
		return currentIt == endIt;
	}
	void Next ( void )
	{
		if (currentIt == endIt)
		{
			return;
		}
		currentIt++;
	}
private:
	vector<personCar>::const_iterator currentIt;
	vector<personCar>::const_iterator endIt;
};

class CPersonList
{
public:
	CPersonList( vector<personCar>::const_iterator curr, vector<personCar>::const_iterator end)// constructor that fills the iterators
	{
		currentIt = curr;
		endIt = end;
	}
	const string & Name ( void ) const
	{
		return (*currentIt).name;
	}
	const string & Surname ( void )
	{
		return (*currentIt).surname;
	}
	bool AtEnd ( void ) 
	{
		return currentIt == endIt;
	}
	void Next ( void )
	{
		if (currentIt == endIt)
		{
			return;
		}
		personCar currNameSurname;
		currNameSurname.name = (*currentIt).name;
		currNameSurname.surname = (*currentIt).surname;// creating a structure object for easier comparison
		while ((!cmpNameSurname((*currentIt), currNameSurname) && !cmpNameSurname(currNameSurname, (*currentIt))))
		// loop while the current first and last name are equal to the current first and last name in the sorted vector of objects
		{
			currentIt++;
			if (currentIt == endIt)
			{
				return;
			}
		}
	}
private:
	vector<personCar>::const_iterator currentIt;
	vector<personCar>::const_iterator endIt;
};



class CRegister
{
private:
	vector<personCar> personsCarsByName;// vector in which objects are sorted by last name and first name
	vector<personCar> personsCarsByRZ;// vector in which objects are sorted by car number
public:
	CRegister()
	{

	}
	~CRegister()
	{
		// since vector containers are used and memory is not allocated anywhere, there is no need to delete something manually
	}
	CRegister ( const CRegister & src ) = delete;
	CRegister & operator = ( const CRegister & src ) = delete;

	bool AddCar ( const string & rz, const string & name, const string & surname )
	{
		personCar perCar;
		perCar.name = name;
		perCar.surname = surname;
		perCar.RZ = rz;// fill the object with the passed parameters

		if (personsCarsByName.size() < 1)// if the lists are empty, insert the object into them
        {
            personsCarsByName.insert( personsCarsByName.begin(), perCar );
            personsCarsByRZ.insert( personsCarsByRZ.begin(), perCar );
            return true;
        }
		if (binary_search(personsCarsByRZ.begin(), personsCarsByRZ.end(), perCar, cmpRZ))// if the object is already in the list
		{
			return false;
		}
		auto p1 = lower_bound(personsCarsByName.begin(), personsCarsByName.end(), perCar, cmpNameSurname);// iterator to the first list
		auto p2 = lower_bound(personsCarsByRZ.begin(), personsCarsByRZ.end(), perCar, cmpRZ);// iterator to the second list
		personsCarsByName.insert( p1, perCar );
		personsCarsByRZ.insert( p2, perCar );
		return true;
    }

    bool DelCar (const string & rz )
    {
        personCar valToDel;
        valToDel.RZ = rz;
        if (!binary_search(personsCarsByRZ.begin(), personsCarsByRZ.end(), valToDel, cmpRZ))// if the car is not found
        {
            return false;
        }
        auto p1 = lower_bound(personsCarsByRZ.begin(), personsCarsByRZ.end(), valToDel, cmpRZ);// find the car in the list of objects sorted by car number

		valToDel.name = (*p1).name;
		valToDel.surname = (*p1).surname;// get the owner's name surname
		
		auto p2 = lower_bound(personsCarsByName.begin(), personsCarsByName.end(), valToDel, cmpNameSurname);// find the owner in a list sorted by name

		while (p2 != personsCarsByName.end())
		// go through all the owner's cars until we find a car with the desired number or reach the end of the list (this cannot happen)
		{
			if ((*p2).RZ == valToDel.RZ)
			{
            	personsCarsByRZ.erase(p1);
            	personsCarsByName.erase(p2);// erase the car in both lists
            	return true;
			}
			p2 = p2 + 1;
		}
        return false;
    }

    bool Transfer ( const string & rz, const string & nName, const string & nSurname)
    {
		personCar a;
		a.RZ = rz;
		a.name = nName;
		a.surname = nSurname;// fill in the structure for searching
		if (!binary_search(personsCarsByRZ.begin(), personsCarsByRZ.end(), a, cmpRZ))// if the car with this number does not exist
		{
			return false;
		}
		auto p2 = lower_bound(personsCarsByRZ.begin(), personsCarsByRZ.end(), a, cmpRZ);
		if (!cmpNameSurname((*p2), a) && !cmpNameSurname(a, (*p2)))// if the car is already owned by the person who needs to transfer it
		{
			return false;
		}
		bool aa = DelCar(rz);// remove the car we want to transfer from the list
		if(!aa) return false;
		if(!AddCar(rz, nName, nSurname)) return false;// insert the car with the new owner back into the list
        return true;
    }
	
	CCarList ListCars ( const string & name, const string & surname ) const
	{
		personCar a;
		a.name = name;
		a.surname = surname;
        auto p1 = lower_bound(personsCarsByName.begin(), personsCarsByName.end(), a, cmpNameSurname);// iterator to the first object with the same name
        auto p2 = upper_bound(personsCarsByName.begin(), personsCarsByName.end(), a, cmpNameSurname);// iterator to the last object with the same name
		CCarList nl(p1,p2);
		return nl;
	}
    
	int	CountCars(const string & name, const string & surname ) const
    {
        personCar a;
		a.name = name;
		a.surname = surname;
        auto p1 = lower_bound(personsCarsByName.begin(), personsCarsByName.end(), a, cmpNameSurname);// iterator to the first object with the same name
        auto p2 = upper_bound(personsCarsByName.begin(), personsCarsByName.end(), a, cmpNameSurname);// iterator to the last object with the same name
        return (int)distance(p1, p2);// since each object contains a different auto, it is enough just to count their number
    }
	CPersonList ListPersons( void ) const
	{
		CPersonList nl(personsCarsByName.begin(), personsCarsByName.end());// pass iterators to the beginning and end of the list sorted by name
		return nl;
	}
	friend bool cmpNameSurname(const personCar &pc1, const personCar &pc2);
	friend bool cmpRZ(const personCar &pc1, const personCar &pc2);
};

	

#ifndef __PROGTEST__
bool checkPerson					 ( CRegister		& r,
															const string & name,
															const string & surname,
															vector<string> result )
{
	 for ( CCarList l = r . ListCars ( name, surname ); ! l . AtEnd (); l . Next () )
	 {
		 auto pos = find ( result . begin (), result . end (), l . RZ () ); 
		 if ( pos == result . end () )
			 return false;
		 result . erase ( pos );
	 }
	 return result . size () == 0;
}
int main ( void )
{
	CRegister b1;
	assert ( b1 . AddCar ( "ABC-12-34", "John", "Smith" ) == true );
	assert ( b1 . AddCar ( "ABC-32-22", "John", "Hacker" ) == true );
	assert ( b1 . AddCar ( "XYZ-11-22", "Peter", "Smith" ) == true );
	assert ( b1 . CountCars ( "John", "Hacker" ) == 1 );
	assert ( checkPerson ( b1, "John", "Hacker", { "ABC-32-22" } ) );
	assert ( b1 . Transfer ( "XYZ-11-22", "John", "Hacker" ) == true );
	assert ( b1 . AddCar ( "XYZ-99-88", "John", "Smith" ) == true );
	assert ( b1 . CountCars ( "John", "Smith" ) == 2 );
	assert ( checkPerson ( b1, "John", "Smith", { "ABC-12-34", "XYZ-99-88" } ) );
	assert ( b1 . CountCars ( "John", "Hacker" ) == 2 );
	assert ( checkPerson ( b1, "John", "Hacker", { "ABC-32-22", "XYZ-11-22" } ) );
	assert ( b1 . CountCars ( "Peter", "Smith" ) == 0 );
	assert ( checkPerson ( b1, "Peter", "Smith", {	} ) );


	assert ( b1 . Transfer ( "XYZ-11-22", "Jane", "Black" ) == true );

	assert ( b1 . CountCars ( "Jane", "Black" ) == 1 );
	assert ( checkPerson ( b1, "Jane", "Black", { "XYZ-11-22" } ) );
	assert ( b1 . CountCars ( "John", "Smith" ) == 2 );
	assert ( checkPerson ( b1, "John", "Smith", { "ABC-12-34", "XYZ-99-88" } ) );
	assert ( b1 . DelCar ( "XYZ-11-22" ) == true );
	assert ( b1 . CountCars ( "Jane", "Black" ) == 0 );
	assert ( checkPerson ( b1, "Jane", "Black", {	} ) );
	assert ( b1 . AddCar ( "XYZ-11-22", "George", "White" ) == true );



	 CPersonList i1 = b1 . ListPersons ();

	assert ( ! i1 . AtEnd () && i1 . Surname () == "Hacker" && i1 . Name () == "John" );
	assert ( checkPerson ( b1, "John", "Hacker", { "ABC-32-22" } ) );
	i1 . Next ();
	assert ( ! i1 . AtEnd () && i1 . Surname () == "Smith" && i1 . Name () == "John" );
	assert ( checkPerson ( b1, "John", "Smith", { "ABC-12-34", "XYZ-99-88" } ) );
	i1 . Next ();
	assert ( ! i1 . AtEnd () && i1 . Surname () == "White" && i1 . Name () == "George" );
	assert ( checkPerson ( b1, "George", "White", { "XYZ-11-22" } ) );
	i1 . Next ();
	assert ( i1 . AtEnd () );

	CRegister b2;
	assert ( b2 . AddCar ( "ABC-12-34", "John", "Smith" ) == true );
	assert ( b2 . AddCar ( "ABC-32-22", "John", "Hacker" ) == true );
	assert ( b2 . AddCar ( "XYZ-11-22", "Peter", "Smith" ) == true );
	assert ( b2 . AddCar ( "XYZ-11-22", "Jane", "Black" ) == false );
	assert ( b2 . DelCar ( "AAA-11-11" ) == false );
	assert ( b2 . Transfer ( "BBB-99-99", "John", "Smith" ) == false );
	assert ( b2 . Transfer ( "ABC-12-34", "John", "Smith" ) == false );
	assert ( b2 . CountCars ( "George", "White" ) == 0 );
	assert ( checkPerson ( b2, "George", "White", {	} ) );
	CPersonList i2 = b2 . ListPersons ();
	assert ( ! i2 . AtEnd () && i2 . Surname () == "Hacker" && i2 . Name () == "John" );
	assert ( checkPerson ( b2, "John", "Hacker", { "ABC-32-22" } ) );
	i2 . Next ();
	assert ( ! i2 . AtEnd () && i2 . Surname () == "Smith" && i2 . Name () == "John" );
	assert ( checkPerson ( b2, "John", "Smith", { "ABC-12-34" } ) );
	i2 . Next ();
	assert ( ! i2 . AtEnd () && i2 . Surname () == "Smith" && i2 . Name () == "Peter" );
	assert ( checkPerson ( b2, "Peter", "Smith", { "XYZ-11-22" } ) );
	i2 . Next ();
	assert ( i2 . AtEnd () );
	cout << 1;
	return 0;
}
#endif /* __PROGTEST__ */
