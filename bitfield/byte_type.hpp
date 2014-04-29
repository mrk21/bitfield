#ifndef __INCLUDED_BITFIELD_BYTE_TYPE_HPP__
#define __INCLUDED_BITFIELD_BYTE_TYPE_HPP__

#include <bitfield/bit_type.hpp>

namespace bitfield {
    class byte_type {
        bit_type v;
        
    public:
        constexpr byte_type(uint32_t v) : v(v<<3) {}
        
        constexpr uint32_t bit() const {
            return this->v.bit();
        }
        
        constexpr uint32_t byte() const {
            return this->v.byte();
        }
        
        constexpr uint32_t max_value() const {
            return this->v.max_value();
        }
        
        constexpr byte_type add(byte_type target) const {
            return this->v.add(target.v).byte();
        }
        
        constexpr byte_type diff(byte_type target) const {
            return this->v.diff(target.v).byte();
        }
        
        template<typename T = uint8_t, typename U>
        constexpr T * addr(const U * base_addr) const {
            return this->v.addr<T>(base_addr);
        }
    };
    
    inline constexpr byte_type operator "" _byte(unsigned long long int value) { return value; }
}

#endif // __INCLUDED_BITFIELD_BYTE_TYPE_HPP__
