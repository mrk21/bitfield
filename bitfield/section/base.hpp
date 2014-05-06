#ifndef __INCLUDED_BITFIELD_SECTION_BASE_HPP__
#define __INCLUDED_BITFIELD_SECTION_BASE_HPP__

#include <bitfield/section/traits.hpp>
#include <cstddef>
#include <cstdint>

namespace bitfield { namespace section {
    // You must define the methods and types listed below.
    // 
    // Derived class:
    //   const uint8_t * base_addr() const; // Return an address of the first fieldset.
    //   std::size_t length() const; // Return a total byte of the sections.
    // 
    // Parent class:
    //   using base_class = <base class>; // The base class of the Parent class.
    //                                    // But not needed when the Parent class not inherited.
    template<class Derived, class FieldSet, class Parent>
    class base {
        using self = base;
        
    public:
        using       iterator =       uint8_t *;
        using const_iterator = const uint8_t *;
        
        static constexpr std::ptrdiff_t offset_from_parent() {
            return parent_traits<Parent>::OFFSET_FROM_PARENT;
        }
        
        base() = default;
        base(const base &) = delete;
        base & operator =(const base &) = delete;
        
        iterator begin() { return this->base_addr();                           }
        iterator   end() { return this->base_addr() + this->derived()->size(); }
        
        const_iterator begin() const { return this->derived()->base_addr();                           }
        const_iterator   end() const { return this->derived()->base_addr() + this->derived()->size(); }
        
        const_iterator cbegin() const { return this->begin(); }
        const_iterator   cend() const { return this->end();   }
        
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
        
        std::size_t size() const {
            return this->derived()->length();
        }
        
              Parent * parent()       { return (      Parent *)((uint8_t *)this - self::offset_from_parent()); }
        const Parent * parent() const { return (const Parent *)((uint8_t *)this - self::offset_from_parent()); }
        
              FieldSet * fieldset()       { return (      FieldSet *)this->base_addr();            }
        const FieldSet * fieldset() const { return (const FieldSet *)this->derived()->base_addr(); }
        
    private:
              Derived * derived()       { return static_cast<      Derived *>(this); }
        const Derived * derived() const { return static_cast<const Derived *>(this); }
    };
}}

#endif // __INCLUDED_BITFIELD_SECTION_BASE_HPP__
