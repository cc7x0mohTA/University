#include "fifteen.h"

/* ***** Part 1 ***** */

// default contructor :

fifteen::fifteen( ) : open_i{dimension-1}, open_j{dimension-1}
{
	for(size_t i = 0; i < dimension; ++i)
	{
		for(size_t j = 0; j < dimension; ++j)
			table[i][j] = dimension*i + j+1;
	}

	table[dimension-1][dimension-1] = 0;
}

// init list: :

fifteen::fifteen( std::initializer_list< std::initializer_list< size_t > > init )
{
	size_t i = 0, j = 0;

	for(auto it_i = init.begin(); i < dimension && it_i != init.end(); ++i, ++it_i)
	{
		j = 0;

		for(auto it_j = (*it_i).begin(); j < dimension && it_j != (*it_i).end(); ++j, ++it_j)
		{
			table[i][j] = *it_j;
			if(*it_j == 0) open_i = i, open_j = j;
		}
	}
}

// printing :

std::ostream& operator << ( std::ostream& stream, const fifteen& f )
{
	for(size_t i = 0; i < f.dimension; ++i)
	{
		for(size_t j = 0; j < f.dimension; ++j)
		{
			stream << f.table[i][j] << "\t";
		}

		stream << "\n";
	}

	return stream;
}

/* ***** Part 2 ***** */

// Position where val must be in the solution.  

std::pair< size_t, size_t > fifteen::solvedposition( size_t val )
{
	std::pair< size_t, size_t > p = std::make_pair((val-1)/dimension, (val-1) % dimension);
	if(val==0) p = std::make_pair(dimension-1, dimension-1);
	return p;
}

size_t fifteen::hashvalue( ) const
{
	size_t w = 0;
	const size_t MOD = 1000000007;

	for(size_t i = 0; i < dimension; ++i)
	{
		for(size_t j = 0; j < dimension; ++j)
		{
			 size_t w1 = ( (i+3) * 17 + (j + 7) * 29);
			 size_t w2 = i + j + 41;
			 w = (( (w+w1) % MOD ) * w2) % MOD;
		}
	}

	return w;
}

bool fifteen::equals( const fifteen& other ) const
{
	for(size_t i = 0; i < dimension; ++i)
	{
		for(size_t j = 0; j < dimension; ++j)
		{
			if(table[i][j] != other.table[i][j]) return false;
		}
	}

	return true;
}

size_t fifteen::distance( ) const
{
	size_t dist = 0;

	for(size_t i = 0; i < dimension; ++i)
	{
		for(size_t j = 0; j < dimension; ++j)
		{
			auto p = solvedposition(table[i][j]);

			dist += distance(p,{i,j});
		}
	}

	return dist;
}

bool fifteen::issolved( ) const
{
	//fifteen ff; return (*this).equals(ff);
	return distance() == 0;
}

void fifteen::makemove(move p)
{
	size_t x = open_i, y = open_j;

 switch (p) {
    case move::left:
      if (y == 0) throw illegalmove(p);
      else {
        std::swap(table[x][y], table[x][y-1]); 
        open_j -= 1;
      }
      break;
    case move::up:
      if (x == 0) throw illegalmove(p);
      else {
        std::swap(table[x][y], table[x-1][y]);
        open_i -= 1;
      }
      break;
    case move::down:
      if (x == dimension-1) throw illegalmove(p);
      else {
        std::swap(table[x][y], table[x+1][y]);
        open_i += 1;
      }
      break;
    case move::right:
      if (y == dimension-1) throw illegalmove(p);
      else {
        std::swap(table[x][y], table[x][y+1]);
        open_j += 1;
      }
      break;
  }

}
