#ifndef __INCLUDED_BITFIELD_HPP__
#define __INCLUDED_BITFIELD_HPP__

#include <iostream>
#include <array>

namespace bitfield {
    class bit_type {
        uint8_t v;
        
    public:
        constexpr bit_type(uint8_t v) : v(v) {}
        
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
        };
        
        template<typename T>
        constexpr uint8_t * addr(const T * addr) const {
            return (uint8_t *)addr + this->byte();
        }
    };
    
    template<uint32_t Size, uint32_t Offset = 0>
    class bitfield {
    public:
        static constexpr uint32_t SIZE = Size;
        static constexpr uint32_t OFFSET = Offset;
        static constexpr uint32_t NEXT_OFFSET = SIZE + OFFSET;
        
        static constexpr uint32_t BYTE = bit_type(SIZE).ceil().byte();
        static constexpr uint32_t PADDING = bit_type(NEXT_OFFSET).ceil().diff(NEXT_OFFSET).bit();
        static constexpr uint32_t MASK = bit_type(SIZE).max_value() << PADDING;
        
        template<uint32_t NextSize>
        using next_bitfield = bitfield<NextSize, NEXT_OFFSET>;
        using container_type = std::array<uint8_t, bit_type(NEXT_OFFSET).ceil().byte()>;
        
        // for Little-Endian
        uint32_t get() const {
            uint32_t value = 0x00;
            uint8_t * addr = bit_type(OFFSET).addr(this);
            uint8_t * value_addr = (uint8_t *)&value;
            
            for (uint32_t i=0; i < BYTE; ++i) {
                value_addr[BYTE-i-1] = addr[i];
            }
            
            value &= MASK;
            value >>= PADDING;
            return value;
        }
        
        // for Little-Endian
        void set(uint32_t value) {
            static constexpr uint32_t clear_mask = ~MASK;
            
            value <<= PADDING;
            value &= MASK;
            
            uint8_t * addr = bit_type(OFFSET).addr(this);
            uint8_t * value_addr = (uint8_t *)&value;
            uint8_t * clear_mask_addr = (uint8_t *)&clear_mask;
            
            for (uint32_t i=0; i < BYTE; ++i) {
                uint32_t j = BYTE-i-1;
                addr[i] &= clear_mask_addr[j];
                addr[i] |= value_addr[j];
            }
        }
        
        operator uint32_t() const {
            return this->get();
        }
        
        bitfield & operator =(uint32_t value) {
            this->set(value);
            return *this;
        }
        
        friend std::ostream & operator <<(std::ostream & out, const bitfield & v) {
            return out << v.get();
        }
    };
}

#endif // __INCLUDED_BITFIELD_HPP__
