#include <iostream>
#include "plf_hive.h"


auto main( ) -> int
{
    plf::hive<int> hive{};
    hive.insert_range( std::array{ 1, 2, 3, 4, 5, 6 } );
    std::printf( "Element: %d\n", *std::next( hive.begin( ), 2 ) );

    return 0;
}