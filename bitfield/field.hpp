#ifndef __INCLUDED_BITFIELD_BITFIELD_HPP__
#define __INCLUDED_BITFIELD_BITFIELD_HPP__

#include <bitfield/bit_type.hpp>
#include <bitfield/byte_type.hpp>
#include <bitfield/container/array.hpp>
#include <cstdint>

namespace bitfield {
    template<uint32_t Size, uint32_t Offset = 0>
    class field {
    public:
        static constexpr uint32_t SIZE = Size;
        static constexpr uint32_t OFFSET = Offset;
        static constexpr uint32_t NEXT_OFFSET = SIZE + OFFSET;
        
        static constexpr uint32_t BYTE = bit_type(SIZE).ceil().byte();
        static constexpr uint32_t PADDING = bit_type(NEXT_OFFSET).ceil().diff(NEXT_OFFSET).bit();
        static constexpr uint32_t MASK = bit_type(SIZE).max_value() << PADDING;
        
        static constexpr uint32_t size() {
            return BYTE;
        }
        
        static constexpr byte_type next_bytes() {
            return bit_type(NEXT_OFFSET).ceil().byte();
        }
        
        template<uint32_t NextSize>
        using next_field = field<NextSize, NEXT_OFFSET>;
        using container_type = container::array<bit_type(NEXT_OFFSET).ceil().byte()>;
        
        field() = default;
        field(const field &) = delete;
        field & operator =(const field &) = delete;
        
        field(uint32_t v) { this->set(v); }
        
        field & operator =(uint32_t rop) {
            this->set(rop);
            return *this;
        }
        
        operator uint32_t() const {
            return this->get();
        }
        
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
    };
}

#endif // __INCLUDED_BITFIELD_BITFIELD_HPP__
