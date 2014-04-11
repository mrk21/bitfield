#include <bandit/bandit.h>
#include <bitfield/bitfield.hpp>
#include <bitfield/section/list.hpp>
#include <bitfield/iostream.hpp>
#include <array>

namespace bitfield { namespace section {
    union list_test {
        using container_type = std::array<uint8_t, 96>;
        
        using sections_length_type =                            bitfield< 8>;
        using v1_type              = sections_length_type::next_bitfield<24>;
        
        union section_type {
            using section_length_type =                           bitfield<8>;
            using v1_type             = section_length_type::next_bitfield<8>;
            
            section_length_type  section_length;
            v1_type  v1;
            
            std::size_t length() const {
                return this->section_length;
            }
        };
        
        struct section_container_type: public list<section_container_type, section_type, list_test> {
            const uint8_t * base_addr() const {
                return bit_type(v1_type::NEXT_OFFSET).addr(this);
            }
            
            std::size_t length() const {
                return this->parent()->sections_length;
            }
        };
        
        container_type  container;
        sections_length_type  sections_length;
        section_container_type  sections;
    };
    
go_bandit([]{
    using namespace bandit;
    
    describe("section::list", [&]{
        list_test * packet;
        
        before_each([&]{
            // 1 packet = 96 byte
            packet = new list_test{{{
                0x18, 0x01, 0xE0, 0xA5,                                                   // sections_length = 24 byte, v1 = 123045
                0x04, 0x10, 0xFF, 0xFF,                                                   // section 1: section_length =  4 byte, v1 = 16
                0x0C, 0xF0, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF, // section 2: section_length = 12 byte, v1 = 240
                0x08, 0x15, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,                          // section 3: section_length =  8 byte, v1 = 21
                
                // padding = 68 byte
                0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF
            }}};
        });
        
        describe("#size()", [&]{
            it("should be the number of fieldsets in the list.", [&]{
                AssertThat(packet->sections.size(), Equals(3));
            });
        });
        
        describe("iterator", [&]{
            it("should iterate each fieldset in the list", [&]{
                auto it = packet->sections.begin();
                auto end = packet->sections.end();
                
                AssertThat(it, not Equals(end));
                AssertThat(it->v1, Equals(16));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->v1, Equals(240));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->v1, Equals(21));
                
                ++it;
                AssertThat(it, Equals(end));
            });
            
            describe("inner iterator", [&]{
                it("should iterate each byte of the fieldset", [&]{
                    auto it = packet->sections.begin();
                    auto it_it = it.begin();
                    auto it_end = it.end();
                    
                    AssertThat(it_it, not Equals(it_end));
                    AssertThat(uint32_t(*it_it), Equals(0x04));
                    
                    ++it_it;
                    AssertThat(it_it, not Equals(it_end));
                    AssertThat(uint32_t(*it_it), Equals(0x10));
                    
                    ++it_it;
                    AssertThat(it_it, not Equals(it_end));
                    AssertThat(uint32_t(*it_it), Equals(0xFF));
                    
                    ++it_it;
                    AssertThat(it_it, not Equals(it_end));
                    AssertThat(uint32_t(*it_it), Equals(0xFF));
                    
                    ++it_it;
                    AssertThat(it_it, Equals(it_end));
                });
            });
        });
    });
});
}}
