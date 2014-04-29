#ifndef __INCLUDED_BITFIELD_UTIL_HPP__
#define __INCLUDED_BITFIELD_UTIL_HPP__

#include <bitfield/byte_type.hpp>
#include <iterator>
#include <string>
#include <cstdio>

namespace bitfield { namespace util {
    template<class Container, typename Value = typename std::iterator_traits<typename Container::const_iterator>::value_type>
    struct hex_dump_traits {
        static constexpr bool IS_SUPPORT = false;
    };
    
    template<class Container>
    struct hex_dump_traits<Container, uint8_t> {
        static constexpr bool IS_SUPPORT = true;
    };
    
    template<class Container>
    inline std::string hex_dump(const Container & container) {
        static_assert(hex_dump_traits<Container>::IS_SUPPORT, "The Container::const_iterator::value_type should be an uint8_t");
        
        char buf[10];
        auto it = container.cbegin();
        auto end = container.cend();
        std::string result = "";
        
        for (byte_type byte(0);  it != end;  byte = byte.add(2_byte)) {
            sprintf(buf, "%04X | ", byte.bit()), result += buf;
            
            for (uint32_t bit = 1; bit <= (2_byte).bit(); ++bit) {
                std::sprintf(buf, "%02X", *it++), result += buf;
                if (it == end) break;
                if (bit != (2_byte).bit()) result += " ";
                if (bit == (1_byte).bit()) result += " ";
            }
            result += "\n";
        }
        return result;
    }
}}

#endif // __INCLUDED_BITFIELD_UTIL_HPP__
