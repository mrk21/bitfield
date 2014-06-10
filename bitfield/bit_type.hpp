#ifndef __INCLUDED_BITFIELD_BIT_TYPE_HPP__
#define __INCLUDED_BITFIELD_BIT_TYPE_HPP__

#include <cstdint>

namespace bitfield {
    class bit_type {
        uint32_t v;
        
    public:
        constexpr bit_type(uint32_t v) : v(v) {}
        
        constexpr operator uint32_t() const {
            return this->bit();
        }
        
        constexpr bit_type floor() const {
            return this->v >> 3 << 3;
        }
        
        constexpr bit_type ceil() const {
            return (this->v + 7) >> 3 << 3;
        }
        
        constexpr uint32_t bit() const {
            return this->v;
        }
        
        constexpr uint32_t byte() const {
            return this->v >> 3;
        }
        
        constexpr uint32_t max_value() const {
            return this->v >= 32 ? 0xffffffff : (0x01 << this->v) - 0x01;
        }
        
        constexpr bit_type add(bit_type target) const {
            return this->v + target.v;
        }
        
        constexpr bit_type diff(bit_type target) const {
            return this->v < target.v ?
                target.v - this->v : this->v - target.v;
        }
        
        template<typename T = uint8_t, typename U>
        constexpr T * addr(const U * base_addr) const {
            return (T *)((uint8_t *)base_addr + this->byte());
        }
    };
    
    inline constexpr bit_type operator "" _bit(unsigned long long int value) { return value; }
}

#endif // __INCLUDED_BITFIELD_BIT_TYPE_HPP__
