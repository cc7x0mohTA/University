#ifndef TREE_INCLUDED
#define TREE_INCLUDED  1

#include <iostream>
#include <vector>
#include <string>

class tree;

// struct trnode should be invisible to the user of tree. This can be 
// obtained by making it a private number of tree. 
// In this exercise, we leave it like this, because it is simpler.
// In real code, trnode should be defined inside tree.


struct trnode 
{
   std::string f;
   std::vector< tree > subtrees;
   
   size_t refcnt;
      // The reference counter: Counts how often this trnode is referred to.

   trnode( const std::string& f, const std::vector< tree > & subtrees, 
           size_t refcnt )
      : f{f},
        subtrees{ subtrees },
        refcnt{ refcnt }
   { }

   trnode( const std::string& f, std::vector< tree > && subtrees,
           size_t refcnt )
      : f{f},
        subtrees{ std::move( subtrees )}, 
        refcnt{ refcnt }
   { }

};

class tree
{

  trnode* pntr;

  public:

  tree( const std::string& f ) : pntr( new trnode( f, { }, 1 )) {}
  tree(const std::string& f, const std::vector< tree > & subtrees) : pntr(new trnode(f,subtrees,1)) {} 
  tree(const std::string& f, std::vector< tree > && subtrees): pntr(new trnode(f,std::move(subtrees),1)) {}

  // Ex 5:

  // 2)

  tree (const tree& t) : pntr(t.pntr) { ++pntr->refcnt; }
  void operator = (tree&& t) { std::swap(pntr,t.pntr); }

  void operator = ( const tree& t );
  ~tree( );

  // 3)

   const std::string& functor( ) const { return pntr->f; }
   const tree& operator [ ] ( size_t i ) const { return pntr->subtrees[i]; }
   size_t nrsubtrees( ) const { return pntr->subtrees.size(); }

   // 5)

    std::string& functor( );

    tree& operator[] ( size_t i )
    {
      ensure_not_shared();
      return pntr -> subtrees[i];
    }


   // 6)

   void replacesubtree( size_t i, const tree& t );

   // Other:

   private: void ensure_not_shared( ); 

};


// 4)

std::ostream& operator << (std::ostream &stream, const tree& t);

// 6)

tree subst( const tree& t, const std::string& var, const tree& val );

#endif
