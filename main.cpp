#include "plf_hive.h"
#include "profiling.h"


auto compare_hive_vector_lookup( )
{
    constexpr int count = 10'000'000;

    plf::hive<int> hive{};
    hive.insert_range( std::ranges::views::iota( 0, count ) );

    std::vector<int> vec( count );
    std::iota( vec.begin( ), vec.end( ), 0 );

    double const vec_at_avg_time  = time_execution( [&] { ( void )vec.at( count / 2 ); } );
    double const hive_at_avg_time = time_execution( [&] { ( void )hive.at( count / 2 ); } );

    std::printf( "Vector 'At' Avg Time: %.8e\n", vec_at_avg_time );
    std::printf( "Hive 'At' Avg Time: %.8e\n", hive_at_avg_time );
}


auto compare_hive_lookups( )
{
    constexpr int count = 10'000'000;

    plf::hive<int> hive{};
    hive.insert_range( std::ranges::views::iota( 0, count ) );

    double const hive_ensure_get_avg_time = time_execution( [&] { ( void )hive.ensure_get( count / 2 ); } );
    double const hive_at_avg_time         = time_execution( [&] { ( void )hive.at( count / 2 ); } );

    std::printf( "Hive 'Ensure Get' Avg Time: %.8e\n", hive_ensure_get_avg_time );
    std::printf( "Hive 'At' Avg Time: %.8e\n", hive_at_avg_time );
}


auto compare_hive_insert( )
{
    constexpr int count               = 1'000'000;
    double const hive_insert_avg_time = time_execution(
        [&]
        {
            plf::hive<int> hive{};
            hive.insert_range( std::ranges::views::iota( 0, count ) );
        } );

    std::printf( "Hive Insertion of %d Elements Avg Time: %.8e\n", count, hive_insert_avg_time );
}


auto main( ) -> int
{
    compare_hive_insert( );
    return 0;
}
