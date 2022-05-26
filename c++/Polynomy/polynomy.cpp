#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <memory>
#endif /* C++ 11 */
using namespace std;
#endif /* __PROGTEST__ */

class CPolynomial
{
public:
    CPolynomial()
	{
		//koef = new vector<double>;
	}
	~CPolynomial()
	{

	}

	const int Degree () const
	{
		int sz = koef.size() - 1;
		for (int i = koef.size() - 1; i > 0; i--)
		{
			if (koef[i] == 0)
			{
				sz--;
			}
			else
			{
				break;
			}
		}
		return sz;
	}

	friend CPolynomial operator+ (const CPolynomial &left, const CPolynomial &right);
    friend CPolynomial operator- (const CPolynomial &left, const CPolynomial &right);

    friend CPolynomial operator* (const CPolynomial &left, const double &right);
    friend CPolynomial operator* (const CPolynomial &left, const CPolynomial &right);

    friend bool operator== (const CPolynomial &l, const CPolynomial &r);
    friend bool operator!= (const CPolynomial &l, const CPolynomial &r);

    double & operator[](const int n)
	{
		isEmpty = false;
		if (n >= (int)koef.size())
		{
			int i = (int)koef.size();
			while (i <= n)
			{
				i++;
				koef.push_back(0);
			}
		}
		return koef[n];
	}

	const double & operator[](const int n) const
	{
		// if (n > koef.size())
		// {
		// 	return 0;
		// }
		return koef[n];
	}

    double operator()(double x) const
	{
		double res = 0, x0 = 1;
		for (int i = 0; i < (int)koef.size();  i++)
		{
			res += x0 * koef[i];
			x0 *= x;
		}
		return res;
	}
	
    friend ostream& operator<< (ostream &out, const CPolynomial &poli);
private:
    vector<double> koef;
	bool isEmpty = true;
};

CPolynomial operator+ (CPolynomial const &left,  CPolynomial const &right)
{
    CPolynomial tmp;
	int a = left.koef.size(), b = right.koef.size();
	if (a > b)
	{
		for (int i = 0; i < a; i++)
		{
			tmp[i] = left[i];
		}
		for (int i = 0; i < b; i++)
		{
			tmp[i] += right[i];
		}
	}
	else
	{
		for (int i = 0; i < b; i++)
		{
			tmp[i] = right[i];
		}
		for (int i = 0; i < a; i++)
		{
			tmp[i] += left[i];
		}
	}
    return tmp;
}

CPolynomial operator- (CPolynomial const &left,  CPolynomial const &right)
{
    CPolynomial tmp;
	int a = left.koef.size(), b = right.koef.size();
	if (a > b)
	{
		for (int i = 0; i < a; i++)
		{
			tmp[i] = left[i];
		}
		for (int i = 0; i < b; i++)
		{
			tmp[i] -= right[i];
		}
	}
	else
	{
		for (int i = 0; i < b; i++)
		{
			tmp[i] = -right[i];
		}
		for (int i = 0; i < a; i++)
		{
			tmp[i] += left[i];
		}
	}
    return tmp;
}

CPolynomial operator* (CPolynomial const &left,  double const &right)
{
    CPolynomial tmp;
	if (right == 0)
	{
		tmp[0] = 0;
		return tmp;
	}
	
    for (int i = 0; i < left.Degree() + 1; i++)
    {
       tmp[i] = left[i] * right;
    }
    return tmp;
}

CPolynomial operator* (CPolynomial const &left,  CPolynomial const &right)
{
    CPolynomial tmp;
    tmp[left.Degree() + right.Degree()] = 0;
    for (int i = 0; i <= left.Degree(); i++)
    {
        for (int j = 0; j <= right.Degree(); j++)
        {
			tmp[i + j] += left[i] * right[j];
        }
    }
    return tmp;
}


bool operator== (const CPolynomial &l, const CPolynomial &r)
{
	if (l.Degree() != r.Degree())
	{
		return false;
	}
	for (int i = 0; i < l.Degree(); i++)
	{
		if (l[i] != r[i])
		{
			return false;
		}
	}
	return true;
}

bool operator!= (const CPolynomial &l, const CPolynomial &r)
{
	return !(l == r);
}

ostream& operator<< (ostream &out, const CPolynomial &poli)
{
	int i = poli.Degree();
	if (poli.isEmpty)
	{
		out << 0;
		return out;
	}
	if (i == 0)
	{
		out << poli[i];
		return out;
	}

	bool isStart = true;
	while (i >= 1)
	{
		if (isStart)
		{
			if (poli[i] > 0)
			{
				if (poli[i] == 1)
				{
					out << "x^" << i;
				}
				else
				{
					out << poli[i] << "*x^" << i;
				}
			}
			else
			{
				if (poli[i] == -1)
				{
					out << "- x^" << i;
				}
				else
				{
					out << "- " << -poli[i] << "*x^" << i;
				}
			}
			i--;
			isStart = false;
			continue;
		}
		
		if (poli[i] == 0)
		{
			i--;
			continue;
		}

		if (poli[i] > 0)
		{
			if (poli[i] == 1)
			{
				out << " + x^" << i;
			}
			else
			{
				out << " + " << poli[i] << "*x^" << i;
			}
		}
		else
		{
			if (poli[i] == -1)
			{
				out << " - x^" << i;
			}
			else
			{
				out << " - " << -poli[i] << "*x^" << i;
			}
		}
		i--;
	}
	
	if ((isStart) && (i == 0))
	{
		if (poli[i] > 0)
		{
			if (poli[i] == 1)
			{
				out << 1;
			}
			else
			{
				out << poli[i];
			}
		}
		else
		{
			if (poli[i] == -1)
			{
				out << "- 1";
			}
			else
			{
				out << "- " << -poli[i];
			}
		}
		i--;
		isStart = false;
		return out;
	}


	if (i == 0)
	{
		if (poli[i] > 0)
		{
			if (poli[i] == 1)
			{
				out << " + 1";
			}
			else
			{
				out << " + " << poli[i];
			}
		}
		else if (poli[i] < 0)
		{
			
			out << " - " << - poli[i];
		}
		i--;
		isStart = false;
	}
	
    return out;
}

#ifndef __PROGTEST__
bool smallDiff ( double a, double b)
{
	return (a == b);
}

bool dumpMatch ( const CPolynomial & x, const vector<double> & ref )
{
	for (size_t i = 0; i < ref.size(); i++)
	{
		if (x[i] != ref[i])
		{
			return false;
		}
	}
	cout << endl;
	return true;
}

int main ( void )
{
	// CPolynomial x;
	// x[1] = 3;
	// CPolynomial y;
	// CPolynomial z;
	// y[3] = 200;
	// y[5] = 100;

	// cout << x << endl;
	// cout << y << endl;
	// z = x * y;
	// cout << z << endl;



	// // x[15] = 123;
	// // //x[0] = -1;
	// //x[2] = 0;
	// // double a = x(3);
	// // cout << " x=3 " << x << " = " << a << "\n";
	// cout << x << endl;
	// cout << y << endl;
	// y = y * x;
	// cout << y << endl;




	// CPolynomial a, b, c;
	// ostringstream out;

	// a[0] = -10;
	// a[1] = 3.5;
	// a[3] = 1;
	// assert ( smallDiff ( a ( 2 ), 5 ) );
	// out . str ("");
	// out << a;
	// assert ( out . str () == "x^3 + 3.5*x^1 - 10" );
	// a = a * -2;
	// assert ( a . Degree () == 3
	// 		&& dumpMatch ( a, vector<double>{ 20.0, -7.0, -0.0, -2.0 } ) );

	// out . str ("");
	// out << a;
	// cout << a;
	// assert ( out . str () == "- 2*x^3 - 7*x^1 + 20" );
	// out . str ("");
	// out << b;
	// assert ( out . str () == "0" );
	// b[5] = -1;
	// out . str ("");
	// out << b;
	// assert ( out . str () == "- x^5" );
	// c = a + b;
	// assert ( c . Degree () == 5
	// 		&& dumpMatch ( c, vector<double>{ 20.0, -7.0, 0.0, -2.0, 0.0, -1.0 } ) );

	// out . str ("");
	// out << c;
	// assert ( out . str () == "- x^5 - 2*x^3 - 7*x^1 + 20" );
	// c = a - b;
	// assert ( c . Degree () == 5
	// 		&& dumpMatch ( c, vector<double>{ 20.0, -7.0, -0.0, -2.0, -0.0, 1.0 } ) );

	// out . str ("");
	// out << c;
	// assert ( out . str () == "x^5 - 2*x^3 - 7*x^1 + 20" );
	// c = a * b;
	// assert ( c . Degree () == 8
	// 		&& dumpMatch ( c, vector<double>{ -0.0, -0.0, 0.0, -0.0, 0.0, -20.0, 7.0, -0.0, 2.0 } ) );

	// out . str ("");
	// out << c;
	// assert ( out . str () == "2*x^8 + 7*x^6 - 20*x^5" );
	// assert ( a != b );
	// b[5] = 0;
	// assert ( !(a == b) );
	// a = a * 0;
	// assert ( a . Degree () == 0
	// 		&& dumpMatch ( a, vector<double>{ 0.0 } ) );

	// assert ( a == b );
	//cout << 1;
	return 0;
}
#endif /* __PROGTEST__ */
//C:\Users\olegb\Documents\Prog\druhiSemesr\c++\3du