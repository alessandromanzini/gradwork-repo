#ifndef GRADWORK_REPO_PROFILING_H
#define GRADWORK_REPO_PROFILING_H

#include <algorithm>
#include <chrono>
#include <numeric>
#include <vector>


template <std::invocable<> TSubjectFn>
double time_execution( TSubjectFn subject, size_t const execution_count = 10U )
{
    if ( execution_count == 0U ) { return 0.0; }

    // 1. Measure execution times
    std::vector<double> execution_times( execution_count );
    std::ranges::generate(
        execution_times, [subject]
        {
            auto const start = std::chrono::high_resolution_clock::now( );
            subject( );
            auto const end = std::chrono::high_resolution_clock::now( );
            return std::chrono::duration<double>( end - start ).count( );
        } );

    // 2. Remove top/bottom 5%
    size_t const trim_count = execution_times.size( ) <= 2U ? 0U : static_cast<size_t>( std::ceil( execution_count * 0.05 ) );
    std::ranges::sort( execution_times );
    auto const [trim_beg, trim_end] =
            std::make_pair( std::next( execution_times.begin( ), trim_count ), std::prev( execution_times.end( ), trim_count ) );

    // 3. Accumulated times and average the result
    double const accumulated_time = std::accumulate( trim_beg, trim_end, 0.0 );
    return accumulated_time / ( execution_count - 2 * trim_count );
}


#endif //!GRADWORK_REPO_PROFILING_H
