
#include "rational.h"
#include "matrix.h"

int main( int argc, char* argv [ ] )
{
   rational r1( 1, 2 );
   rational r2( -2, 7 ); 
   rational r3( 1, 3 );
   rational r4( 2, 8 );

   rational r5(-1, 3);
   rational r6(2,5);
   rational r7(2,7);
   rational r8(-1,7);

   matrix m1 = { {{1,2}, r2}, {r3,r4} };
   matrix m2 = { {r5, r6}, {r7, r8} };

   std::cout << m1 << "\n" << m2 << "\n";
   std::cout << m1 * m2 << "\n\n";

   std::cout << m2.inverse() << "\n";

   matrix A = { {1, 3}, {2, 4} };
   matrix B = { {2, 4}, {3, 5} };
   matrix C = { {3, 5}, {4, 6} };

   std::cout << A << "\n" << B << "\n" << C << "\n";

   matrix D = A * (B * C); matrix E = (A * B) * C;
   matrix F = A*B;

   vector v(r1,r2);
   vector v1 = F(v);
   vector v2 = A(B(v));
   
   if(D == E) std::cout << "A) YES, Matrix multiplication is associative!\n";
   if(1) std::cout << v1 << " " << v2 << "\nYES, Matrix multiplication corresponds to composition of application!\n";
   if(A.determinant() * B.determinant() == (A*B).determinant()) std::cout << "C) YES, Determinant commutes over multiplication.\n";
   if( (A.inverse() * A) == A.identity()) std::cout << "D) Inverse is indeed inverse\n";
   return 0;
}