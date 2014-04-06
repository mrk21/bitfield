#ifndef __INCLUDED_BITFIELD_BIT_TYPE_HPP__
#define __INCLUDED_BITFIELD_BIT_TYPE_HPP__

#include <cstdint>

namespace bitfield {
    class bit_type {
        uint32_t v;
        
    public:
        constexpr bit_type(uint32_t v) : v(v) {}
        
        constexpr bit_type floor() const {
            return bit_type(this->v >> 3 << 3);
        }
        
        constexpr bit_type ceil() const {
            return bit_type((this->v + 7) >> 3 << 3);
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
        
        constexpr bit_type diff(bit_type target) const {
            return bit_type(this->v < target.v ? target.v - this->v
                                               : this->v - target.v);
        }
        
        template<typename T>
        constexpr uint8_t * addr(const T * addr) const {
            return (uint8_t *)addr + this->byte();
        }
    };
    
    inline constexpr bit_type operator "" _bit(unsigned long long int value) { return bit_type(value); }
    inline constexpr bit_type operator "" _byte(unsigned long long int value) { return bit_type(value << 3); }
}

#endif // __INCLUDED_BITFIELD_BIT_TYPE_HPP__
