#include "disjoint_sets.h"
#include <iostream>


int main ()
{

    UnionFind f = UnionFind ( 5 );

    f.unite ( 0, 3 );
    f.unite ( 1, 4 );

    std::cout << "0,3 in same set? " << f.is_connected ( 0, 3 ) << std::endl;
    std::cout << "1,2 in same set? " << f.is_connected ( 1, 2 ) << std::endl;
    for (auto i: f._roots )
          std::cout << i << ' ';
    std::cout << std::endl;

    f.unite( 0,4 );
    std::cout << "0,3 in same set? " << f.is_connected ( 0, 3 ) << std::endl;
    std::cout << "1,2 in same set? " << f.is_connected ( 1, 2 ) << std::endl;
    for (auto i: f._roots )
          std::cout << i << ' ';
    std::cout << std::endl;

    return 0;
}
