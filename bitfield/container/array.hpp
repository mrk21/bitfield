#ifndef __INCLUDED_BITFIELD_CONTAINER_ARRAY_HPP__
#define __INCLUDED_BITFIELD_CONTAINER_ARRAY_HPP__

#include <array>

namespace bitfield { namespace container {
    template<std::size_t N>
    using array = std::array<uint8_t, N>;
}};

#endif // __INCLUDED_BITFIELD_CONTAINER_ARRAY_HPP__
