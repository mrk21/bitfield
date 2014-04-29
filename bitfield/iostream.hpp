#ifndef __INCLUDED_BITFIELD_IOSTREAM_HPP__
#define __INCLUDED_BITFIELD_IOSTREAM_HPP__

#include <bitfield/field.hpp>
#include <cstdint>
#include <iostream>

namespace bitfield {
    template<uint32_t S, uint32_t O>
    inline std::ostream & operator <<(std::ostream & out, const field<S,O> & v) {
        return out << v.get();
    }
}

#endif // __INCLUDED_BITFIELD_IOSTREAM_HPP__
