#include <bandit/bandit.h>
#include <bitfield/bitfield.hpp>

namespace bitfield {
    union bitfield_test {
        using v1_type =               bitfield< 1>;
        using v2_type = v1_type::next_bitfield< 9>;
        using v3_type = v2_type::next_bitfield<14>;
        using v4_type = v3_type::next_bitfield< 8>;
        using container_type = v4_type::container_type;
        
        container_type container;
        v1_type v1;
        v2_type v2;
        v3_type v3;
        v4_type v4;
    };
    
go_bandit([&]{
    using namespace bandit;
    
    describe("bitfield", [&]{
        bitfield_test * subject;
        
        before_each([&]{
            // |1byte        |2byte      |3byte     |4byte      |
            // | 1|000 1100  11|11 1001  0110 1110  |1101 1001  |
            // |v1|v2          |v3                  |v4         |
            // | 1|51          |14702               |217        |
            subject = new bitfield_test{{{
                0b10001100,
                0b11111001,
                0b01101110,
                0b11011001,
            }}};
        });
        
        describe("#get()", [&]{
            describe("v1", [&]{ it("should be 1"    , [&]{ AssertThat(subject->v1.get(), Equals(    1)); }); });
            describe("v2", [&]{ it("should be 51"   , [&]{ AssertThat(subject->v2.get(), Equals(   51)); }); });
            describe("v3", [&]{ it("should be 14702", [&]{ AssertThat(subject->v3.get(), Equals(14702)); }); });
            describe("v4", [&]{ it("should be 217"  , [&]{ AssertThat(subject->v4.get(), Equals(  217)); }); });
        });
        
        describe("#set(uint32_t value)", [&]{
            describe("when v1 is 0", [&]{
                before_each([&]{
                    subject->v1.set(0);
                });
                describe("v1", [&]{ it("should be 0"    , [&]{ AssertThat(subject->v1.get(), Equals(    0)); }); });
                describe("v2", [&]{ it("should be 51"   , [&]{ AssertThat(subject->v2.get(), Equals(   51)); }); });
                describe("v3", [&]{ it("should be 14702", [&]{ AssertThat(subject->v3.get(), Equals(14702)); }); });
                describe("v4", [&]{ it("should be 217"  , [&]{ AssertThat(subject->v4.get(), Equals(  217)); }); });
            });
            
            describe("when v2 is 120", [&]{
                before_each([&]{
                    subject->v2.set(120);
                });
                describe("v1", [&]{ it("should be 1"    , [&]{ AssertThat(subject->v1.get(), Equals(    1)); }); });
                describe("v2", [&]{ it("should be 120"  , [&]{ AssertThat(subject->v2.get(), Equals(  120)); }); });
                describe("v3", [&]{ it("should be 14702", [&]{ AssertThat(subject->v3.get(), Equals(14702)); }); });
                describe("v4", [&]{ it("should be 217"  , [&]{ AssertThat(subject->v4.get(), Equals(  217)); }); });
            });
            
            describe("when v3 is 48", [&]{
                before_each([&]{
                    subject->v3.set(48);
                });
                describe("v1", [&]{ it("should be 1"  , [&]{ AssertThat(subject->v1.get(), Equals(  1)); }); });
                describe("v2", [&]{ it("should be 51" , [&]{ AssertThat(subject->v2.get(), Equals( 51)); }); });
                describe("v3", [&]{ it("should be 48" , [&]{ AssertThat(subject->v3.get(), Equals( 48)); }); });
                describe("v4", [&]{ it("should be 217", [&]{ AssertThat(subject->v4.get(), Equals(217)); }); });
            });
            
            describe("when v4 is 123", [&]{
                before_each([&]{
                    subject->v4.set(123);
                });
                describe("v1", [&]{ it("should be 1"    , [&]{ AssertThat(subject->v1.get(), Equals(    1)); }); });
                describe("v2", [&]{ it("should be 51"   , [&]{ AssertThat(subject->v2.get(), Equals(   51)); }); });
                describe("v3", [&]{ it("should be 14702", [&]{ AssertThat(subject->v3.get(), Equals(14702)); }); });
                describe("v4", [&]{ it("should be 123"  , [&]{ AssertThat(subject->v4.get(), Equals(  123)); }); });
            });
        });
    });
});
}
