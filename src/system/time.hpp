#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include "../type.hpp"

namespace sgl
{
    Int64 get_current_time_nanoseconds()
    {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    Float64 get_current_time()
    {
        return static_cast<Float64>(get_current_time_nanoseconds()) /
               static_cast<Float64>(std::nano::den);
    }

} // namespace sgl

#endif
