#ifndef __INCLUDED_BITFIELD_SECTION_TRAITS_HPP__
#define __INCLUDED_BITFIELD_SECTION_TRAITS_HPP__

namespace bitfield { namespace section {
    template<class Parent>
    class parent_traits {
        using self = parent_traits;
        
        template<class P>
        static constexpr std::ptrdiff_t offset_from_parent_(typename P::base_class *) {
            return sizeof(typename P::base_class);
        }
        
        template<class P>
        static constexpr std::ptrdiff_t offset_from_parent_(...) {
            return 0;
        }
        
    public:
        static constexpr std::ptrdiff_t OFFSET_FROM_PARENT =
            self::offset_from_parent_<Parent>(static_cast<Parent *>(nullptr));
    };
}}

#endif // __INCLUDED_BITFIELD_SECTION_TRAITS_HPP__
