#ifndef TYPE_HPP
#define TYPE_HPP

#include <cstdint>
#include <string>

namespace sgl
{
    using Bool = bool;
    using Byte = std::uint8_t;
    using Char = char;
    using SizeT = std::size_t;

    using Int8 = std::int8_t;
    using Int16 = std::int16_t;
    using Int32 = std::int32_t;
    using Int64 = std::int64_t;

    using UInt8 = std::uint8_t;
    using UInt16 = std::uint16_t;
    using UInt32 = std::uint32_t;
    using UInt64 = std::uint64_t;

    using Float32 = float;
    using Float64 = double;

    using String = std::string;

} // namespace sgl

#endif
