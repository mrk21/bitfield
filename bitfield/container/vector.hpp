#ifndef __INCLUDED_BITFIELD_CONTAINER_VECTOR_HPP__
#define __INCLUDED_BITFIELD_CONTAINER_VECTOR_HPP__

#include <vector>

namespace bitfield { namespace container {
    template<class Allocator = std::allocator<uint8_t>>
    using basic_vector = std::vector<uint8_t, Allocator>;
    
    using vector = basic_vector<>;
}};

#endif // __INCLUDED_BITFIELD_CONTAINER_VECTOR_HPP__
