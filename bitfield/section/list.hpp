#ifndef __INCLUDED_BITFIELD_SECTION_LIST_HPP__
#define __INCLUDED_BITFIELD_SECTION_LIST_HPP__

#include <iterator>

namespace bitfield { namespace section {
    // You must define the methods listed below.
    // 
    // Derived class:
    //   const uint8_t * base_addr() const; // Return an address of the first fieldset.
    //   std::size_t length() const; // Return a total byte of the sections.
    // 
    // FieldSet class:
    //   std::size_t length() const; // Return a byte of the fieldset.
    template<class Derived, class FieldSet, class Parent>
    class list {
        template<class CVFieldSet, typename CVUint8_t>
        class iterator_base: public std::iterator<std::forward_iterator_tag, CVFieldSet> {
            CVUint8_t * addr;
            
        public:
            using       iterator =       CVUint8_t *;
            using const_iterator = const CVUint8_t *;
            
            iterator_base(CVUint8_t * addr) : addr(addr) {}
            
            CVFieldSet * operator ->() const {
                return this->fieldset();
            }
            
            CVFieldSet & operator *() const {
                return *this->fieldset();
            }
            
            iterator_base & operator ++() {
                this->addr += this->length();
                return *this;
            }
            
            iterator_base operator ++(int) {
                iterator_base it = *this;
                ++(*this);
                return it;
            }
            
            friend bool operator !=(iterator_base lop, iterator_base rop) {
                return lop.addr != rop.addr;
            }
            
            friend bool operator ==(iterator_base lop, iterator_base rop) {
                return !(lop != rop);
            }
            
            std::size_t length() const {
                return this->fieldset()->length();
            }
            
            std::size_t size() const {
                return this->length();
            }
            
            iterator begin() const { return iterator(this->addr);                  }
            iterator   end() const { return iterator(this->addr + this->length()); }
            
            const_iterator cbegin() const { return const_iterator(this->addr);                  }
            const_iterator   cend() const { return const_iterator(this->addr + this->length()); }
            
            CVFieldSet * fieldset() const { return (CVFieldSet *)this->addr; }
        };
        
    public:
        using       iterator = iterator_base<      FieldSet,       uint8_t>;
        using const_iterator = iterator_base<const FieldSet, const uint8_t>;
        
        iterator begin() { return iterator(this->base_addr());                             }
        iterator   end() { return iterator(this->base_addr() + this->derived()->length()); }
        
        const_iterator begin() const { return const_iterator(this->derived()->base_addr());                             }
        const_iterator   end() const { return const_iterator(this->derived()->base_addr() + this->derived()->length()); }
        
        const_iterator cbegin() const { return this->begin(); }
        const_iterator   cend() const { return this->end();   }
        
        uint8_t * base_addr() {
            return const_cast<uint8_t *>(this->derived()->base_addr());
        }
        
        std::ptrdiff_t offset() const {
            return this->derived()->base_addr() - (uint8_t *)this;
        }
        
        std::size_t size() const {
            std::size_t n = 0;
            for (auto it = this->begin(); it != this->end(); ++it) ++n;
            return n;
        }
        
              Parent * parent()       { return (      Parent *)this; }
        const Parent * parent() const { return (const Parent *)this; }
        
    private:
              Derived * derived()       { return static_cast<      Derived *>(this); }
        const Derived * derived() const { return static_cast<const Derived *>(this); }
    };
}}

#endif // __INCLUDED_BITFIELD_SECTION_LIST_HPP__
