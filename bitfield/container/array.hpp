#ifndef __INCLUDED_BITFIELD_CONTAINER_HPP__
#define __INCLUDED_BITFIELD_CONTAINER_HPP__

#include <array>

namespace bitfield { namespace container {
    template<std::size_t N>
    using array = std::array<uint8_t, N>;
}};

#endif // __INCLUDED_BITFIELD_CONTAINER_HPP__
