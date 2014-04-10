#ifndef __INCLUDED_BITFIELD_SECTION_LIST_HPP__
#define __INCLUDED_BITFIELD_SECTION_LIST_HPP__

#include <iterator>

namespace bitfield { namespace section {
    // You must define the methods listed below.
    // 
    // Derived class:
    //   uint8_t * base_addr(); // Return an address of the first section.
    //   std::size_t length() const; // Return a total byte of the all sections.
    // 
    // Section class:
    //   std::size_t length() const; // Return a byte of the section.
    template<class Derived, class Section>
    class list {
    public:
        class iterator: public std::iterator<std::forward_iterator_tag, Section> {
            uint8_t * addr;
            
        public:
            iterator(uint8_t * addr) : addr(addr) {}
            
            Section * operator ->() const {
                return (Section *)(this->addr);
            }
            
            Section & operator *() const {
                return *(Section *)(this->addr);
            }
            
            iterator & operator ++() {
                this->addr += ((Section *)this->addr)->length();
                return *this;
            }
            
            bool operator !=(iterator rop) const {
                return this->addr != rop.addr;
            }
        };
        
        iterator begin() {
            return iterator(static_cast<Derived *>(this)->base_addr());
        }
        
        iterator end() {
            return iterator(static_cast<Derived *>(this)->base_addr() + static_cast<Derived *>(this)->length());
        }
    };
}}

#endif // __INCLUDED_BITFIELD_SECTION_LIST_HPP__
