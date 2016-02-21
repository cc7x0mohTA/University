#ifndef STACK_INCLUDED
#define STACK_INCLUDED 1

#include <cstddef>
#include <iostream>
#include <initializer_list>

class stack
{
	size_t current_size;
	size_t current_capacity;
	double* tab;

	friend std::ostream& operator << ( std::ostream& stream, const stack& s );

	void ensure_capacity( size_t c );

	public:

	// Complete:

	void operator = ( const stack& s );
	void push( double d );
	stack( const stack& s );
	stack( );
	~stack() { delete[] tab; }
	void pop( );
	void reset( size_t s );
	double& top( ) { return tab[current_size-1]; }
	double top( ) const { return tab[current_size-1]; }
	size_t size( ) const { return current_size; }
	bool empty( ) const { return current_size == 0; }

	// Ex4

	friend stack operator+ ( const stack& s1, const stack& s2 );

	double operator[] ( unsigned int i ) const { return tab[current_size-i-1]; }
	double& operator[] (unsigned int i) { return tab[current_size-i-1]; }

	stack(std::initializer_list<double> List)
	{
		current_size = List.size();
		current_capacity = 2 * current_size;
		tab = new double[current_capacity];
		size_t i = 0;
		for(auto it = List.begin(); it != List.end(); ++it) { tab[i] = *it; i++; }
	}
	
	void operator += (double x) { push(x); }
	void operator += ( const stack& s )
	{
		stack S = s;
		while(S.size() > 0) { push(S.top()); S.pop(); }
	}
};

#endif