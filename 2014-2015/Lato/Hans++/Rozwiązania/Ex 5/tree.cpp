#include "tree.h"

// 2)

void tree::operator = (const tree& t)
{
#if 0
	++ ( t. pntr -> refcnt );
	-- ( pntr -> refcnt );
	auto p = t.pntr;
	if( pntr -> refcnt == 0 )
		delete pntr;
	pntr = p;
#endif
	*this = tree(t);
}

tree::~tree()
{
    pntr->refcnt--;
    if(pntr->refcnt == 0) delete pntr;
}

// 4)

std::ostream& operator << ( std::ostream& stream, const tree& t ) 
{ 
	stream<<t.functor()<<'\n';
	if(t.nrsubtrees() == 0) return stream;
	else for(size_t i = 0; i < t.nrsubtrees(); ++i)  stream << t[i] << " ";

	return stream;
}

// 5:

void tree::ensure_not_shared()
{
	if (pntr -> refcnt != 1)
	{
		pntr -> refcnt--;
		pntr = new trnode(pntr -> f, pntr -> subtrees, 1);
	}
}

std::string& tree::functor()
{
	ensure_not_shared();
	return pntr -> f;
}

// 6:

void tree::replacesubtree( size_t i, const tree& t )
{
	if( pntr -> subtrees[i]. pntr != t. pntr )
	{
		ensure_not_shared( );
		pntr -> subtrees[i] = t;
	}
}

tree subst( const tree& t, const std::string& var, const tree& val )
{
	if( t. nrsubtrees( ) == 0 )
	{
		if( t. functor( ) == var ) return val;
		else return t;
	}
	else
	{
		tree res = t;
		for( size_t i = 0; i < t. nrsubtrees( ); ++ i )
			res. replacesubtree( i, subst( t[i], var, val ));
		return res;
	}
}