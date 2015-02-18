#include "stack.h"

void stack::ensure_capacity( size_t c )
{
	if( current_capacity < c )
	{
		if( c < 2 * current_capacity )
			c = 2 * current_capacity;

		double* newtab = new double[ c ];

		for( size_t i = 0; i < current_size; ++ i ) newtab[i] = tab[i];

		current_capacity = c;
		delete[] tab;
		tab = newtab;
	}
}

void stack::reset( size_t s )
{
	while(current_size > s)
	{
		pop();
		current_size--;
	}
}

void stack::pop() { current_size--; }

void stack::push( double d )
{
	ensure_capacity( current_size + 1 );
	tab[current_size] = d; current_size++;
}

stack::stack() : current_size{0}, current_capacity{8},tab{new double[8]} {}

stack::stack( const stack& s ) : current_size{s.size()}, current_capacity{s.current_capacity}, tab{new double[s.current_capacity]}
{
	for(size_t i = 0; i < s.size(); i++) tab[i] = s.tab[i];
}

void stack::operator = (const stack &s)
{
	if(s.tab == tab) return;

	delete[] tab; tab = new double[s.current_capacity];
	current_size = s. current_size;
	current_capacity = s. current_capacity;

	for(size_t i = 0; i < s. current_size; i++) tab[i] = s.tab[i];
}