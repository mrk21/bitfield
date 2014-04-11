#ifndef __INCLUDED_BITFIELD_CONTAINER_BASE_HPP__
#define __INCLUDED_BITFIELD_CONTAINER_BASE_HPP__

#include <cstddef>
#include <cstdint>

namespace bitfield { namespace container {
    // You must define the methods listed below to the Derived class.
    // 
    // const uint8_t * base_addr() const; // Return an address of the first byte.
    // std::size_t size() const; // Return a byte of the container.
    template<class Derived, class FieldSet, class Parent>
    class base {
    public:
        using iterator = uint8_t *;
        using const_iterator = const uint8_t *;
        
        iterator begin() { return this->base_addr();                           }
        iterator   end() { return this->base_addr() + this->derived()->size(); }
        
        const_iterator begin() const { return this->derived()->base_addr();                           }
        const_iterator   end() const { return this->derived()->base_addr() + this->derived()->size(); }
        
              FieldSet & operator *()       { return *this->fieldset(); }
        const FieldSet & operator *() const { return *this->fieldset(); }
        
              FieldSet * operator ->()       { return this->fieldset(); }
        const FieldSet * operator ->() const { return this->fieldset(); }
        
        uint8_t * base_addr() {
            return const_cast<uint8_t *>(this->derived()->base_addr());
        }
        
        std::ptrdiff_t offset() const {
            return this->derived()->base_addr() - (uint8_t *)this;
        }
        
              Derived * derived()       { return static_cast<      Derived *>(this); }
        const Derived * derived() const { return static_cast<const Derived *>(this); }
        
              Parent * parent()       { return (      Parent *)this; }
        const Parent * parent() const { return (const Parent *)this; }
        
              FieldSet * fieldset()       { return (      FieldSet *)this->base_addr();            }
        const FieldSet * fieldset() const { return (const FieldSet *)this->derived()->base_addr(); }
    };
}}

#endif // __INCLUDED_BITFIELD_CONTAINER_BASE_HPP__
