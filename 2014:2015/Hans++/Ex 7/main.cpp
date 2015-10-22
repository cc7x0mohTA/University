#include <iostream>
#include <vector>
#include <list>
#include "rational.h"

using namespace std;

struct xx
{
	int val;
	static unsigned int copied;
	static unsigned int moved;
	
	explicit xx( int val ) : val{val} { }
	
	xx( xx&& x ) noexcept : val{ x.val } 
	{
		//std::cout << "move constr " << this << "\n";
		++ moved;
	}

	xx( const xx& x ) : val{ x.val }
	{
		//std::cout << "copy constr " << this << "\n";
		++ copied;
	}
};

unsigned int xx::copied = 0;
unsigned int xx::moved = 0;

struct yy
{
        int val;
        static unsigned int copied;
        static unsigned int moved;
    
        explicit yy( int val ) : val{val} { } 
    
        yy( yy&& x ) : val{ x.val } {++moved;}  
        yy( const yy& x ) : val{x.val} {++ copied;}
};

unsigned int yy::copied = 0;
unsigned int yy::moved = 0;


// 1)

void Ex1()
{
	cout << "START OF Ex1\n";
	vector<xx> V;

	for(int i = 0; i < 16; i++)
	{
		V.push_back(xx{i});
	}

	// with noexcept Copied : 0 , moved : 2048575
	// without noexcept : Copied : 1048575 , moved : 1000000

	std::cout << "Copied : " << xx::copied << " " << ", moved : " << xx::moved << "\n";

	cout << V.capacity() << "\n";

	cout << "cap : " << V.capacity() << "\n";
	while(V.empty() == false) V.pop_back();
	cout << "cap : " << V.capacity() << "\n";

	vector<int> myvector;
	myvector.reserve(1000);
	for (int i=0; i<100; i++) myvector.push_back(i);
	
	std::cout << "size: " << (int) myvector.size() << '\n';
	std::cout << "capacity: " << (int) myvector.capacity() << '\n';
	std::cout << "max_size: " << (int) myvector.max_size() << '\n';

	cout << "END of Ex 1\n";
}

void Ex2()
{
	cout << "START OF Ex2\n";
	list<yy> V;

        for(int i = 0; i < 1000000; i++)
        {
		V.emplace_back(i);
        }

	// Copied : 0 , moved : 1000000
        std::cout << "Copied : " << yy::copied << " " << ", moved : " << yy::moved << "\n";

        cout << "END of Ex 2\n";
}

// 3)

double average(std::vector<double> &V)
{
	if(V.size() == 0) return 0.0;

	double sum = 0.0;
	for(auto i : V) sum += i;
	return (sum / V.size());
}

// 4)

template< typename X > std::ostream& operator << (std::ostream & out, const std::vector<X> &vect )
{
	out << "[ ";
	for(int i = 0; i < vect.size()-1; i++) out << vect[i] << ", ";
	out << vect[vect.size()-1] << " ]";
	return out;	
}

template< typename X > X average( const std::vector<X> & vect )
{
	X result = 0;
	for(auto i : vect) result = result + i;	
	return (result / vect.size());
}

void averageTest()
{
	vector<rational> A {  rational{1,2}, rational{3,4}, rational{2,1} };
	std::cout << "A : " << average<rational>(A) << "\n";
	vector<float> B { 4.5f, 4.1f, 3.2f };
	std::cout << "B : " << average<float>(B) << "\n";
	vector<double> C {2.1, 6.4, 2.55, 6.3, 2.1};
	std::cout << "C : " << average<double>(C) << "\n";
}

// 5 )

vector<double> multiply( const std::vector<double> &p1, const std::vector<double> &p2 )
{
	size_t m = p1.size(), n = p2.size();
	vector<double> prod(m + n - 1, 0.0);
	
	for(size_t i=0; i<m; i++)
	{
		for(size_t j = 0; j < n; j++)
		{
			prod[i+j] += p1[i] * p2[j];
		}
	}
 

	return prod;
}

void polynomialMultiplicationTest()
{
	vector< vector<double> >V(9);

	for(int i = 1; i <= 9; i++)
	{
		V[i-1] = {0.1*i, 1.0};
	}

	vector<double> sol{1};

	for(int i = 0; i < 9; i++) sol = multiply(sol, V[i]);
	
	cout << "(x+0.1) * (x+0.2) * ... * (x+0.9) = [" << sol << "]\n";
}

// 6)

template <typename T> class Polynomial
{
	public: 

	vector<T> A;
	Polynomial(vector<T> _A) : A{_A} {}
};

template <typename T> Polynomial<T> operator* (const Polynomial<T> &A, const Polynomial<T> &B)
{
        int m = A.A.size(), n = B.A.size();
	vector<T> prod(m + n - 1, 0);
            
	for(int i=0; i<m; i++)
	{   
       	        for(int j = 0; j < n; j++)
		{   
                       	prod[i+j] = prod[i+j] +  A.A[i] * B.A[j];
               	}   
	}
 
	return Polynomial<T>{prod};
}

void polynomialClassTest()	// Calculating (x+1/2)^5
{
	vector<rational> V{ rational{1,2}, rational{1} };
	vector<rational> W{ rational{1} };

	Polynomial<rational> P(V), Q(W);

	for(int i = 1; i <= 5; i++) Q = Q * P;

	cout << Q.A << "\n";
}


int main()
{
	//Ex1();
	//Ex2();	
	//averageTest();
	polynomialMultiplicationTest();
	polynomialClassTest();
	return 0;
}
