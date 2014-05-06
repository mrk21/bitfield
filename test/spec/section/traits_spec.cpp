#include <bandit/bandit.h>
#include <bitfield/section/traits.hpp>

namespace bitfield { namespace section {
    namespace parent_traits_test {
        struct base {
            int v;
        };
        
        struct type1: public base {
            using base_class = base;
            static constexpr std::ptrdiff_t offset() { return parent_traits<type1>::OFFSET_FROM_PARENT; }
            int u;
        };
        
        struct type2: public base {
            static constexpr std::ptrdiff_t offset() { return parent_traits<type2>::OFFSET_FROM_PARENT; }
            int u;
        };
        
        struct type3 {
            static constexpr std::ptrdiff_t offset() { return parent_traits<type3>::OFFSET_FROM_PARENT; }
            int u;
        };
        
        struct type4 {
            using base_class = base;
            static constexpr std::ptrdiff_t offset() { return parent_traits<type4>::OFFSET_FROM_PARENT; }
            int u;
        };
    };
    
go_bandit([]{
    using namespace bandit;
    
    describe("section::parent_t::traits<Parent>", [&]{
        namespace t = parent_traits_test;
        
        describe("::OFFSET_FROM_PARENT", [&]{
            describe("When the Parent inherited, and it defined the base_class", [&]{
                it("should be size of the base_class", [&]{
                    AssertThat(t::type1::offset(), Equals(sizeof(t::base)));
                });
            });
            
            describe("When the Parent inherited, and it not defined the base_class", [&]{
                it("should be 0", [&]{
                    AssertThat(t::type2::offset(), Equals(0));
                });
            });
            
            describe("When the Parent not inherited, and it not defined the base_class", [&]{
                it("should be 0", [&]{
                    AssertThat(t::type3::offset(), Equals(0));
                });
            });
            
            describe("When the Parent not inherited, and it defined the base_class", [&]{
                it("should be 0", [&]{
                    AssertThat(t::type4::offset(), Equals(0));
                });
            });
        });
    });
});
}}
