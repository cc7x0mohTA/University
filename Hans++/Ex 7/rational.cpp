
#include "rational.h"
#include <iostream>

// Complete these methods:

int rational::gcd( int a, int b )
{
	while ( a != 0 )
	{
		int c = a; a = b%a;  b = c;
	}
	return b;
}

void rational::normalize( )
{
	if(denum == 0)
	{
		throw std::runtime_error( "division by zero");
	}

	int d = rational::gcd(num, denum);
    num /= d; denum /= d;

    if(denum < 0)
	{
		num = -num; denum = -denum;
	}
}

rational operator - ( rational r )
{
	r.num = -r.num; return r;
}

rational operator + ( const rational& r1, const rational& r2 )
{
	int a = r1.getNum(), b = r1.getDenum(), c = r2.getNum(), d = r2.getDenum();
	return { a*d + b*c, b*d };
}

rational operator - ( const rational& r1, const rational& r2 )
{
    rational R = r1 + (-r2);
	return R;
}

rational operator * ( const rational& r1, const rational& r2 )
{
	int a = r1.getNum(), b = r1.getDenum(), c = r2.getNum(), d = r2.getDenum();
	return rational( a*c, b *d );
}

rational operator / ( const rational& r1, const rational& r2 )
{
	int a = r1.getNum(), b = r1.getDenum(), c = r2.getNum(), d = r2.getDenum();
	return rational(a*d, b*c);
}

bool operator == ( const rational& r1, const rational& r2 )
{
	rational R = r1-r2;
	return (R.getNum() == 0 ? true : false);
}

bool operator != ( const rational& r1, const rational& r2 )
{
	return !(r1 == r2);
}

std::ostream& operator << ( std::ostream& stream, const rational& r )
{
	stream << r.getNum() << " / " << r.getDenum();
	return stream;
}