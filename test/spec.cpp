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
    
    describe("bit_type", [&]{
        describe("#floor()", [&]{
            describe("when value is 0" , [&]{ it("should be 0" , [&]{ AssertThat(( 0_bit).floor().bit(), Equals( 0)); }); });
            describe("when value is 1" , [&]{ it("should be 0" , [&]{ AssertThat(( 1_bit).floor().bit(), Equals( 0)); }); });
            describe("when value is 7" , [&]{ it("should be 0" , [&]{ AssertThat(( 7_bit).floor().bit(), Equals( 0)); }); });
            describe("when value is 8" , [&]{ it("should be 8" , [&]{ AssertThat(( 8_bit).floor().bit(), Equals( 8)); }); });
            describe("when value is 9" , [&]{ it("should be 8" , [&]{ AssertThat(( 9_bit).floor().bit(), Equals( 8)); }); });
            describe("when value is 15", [&]{ it("should be 8" , [&]{ AssertThat((15_bit).floor().bit(), Equals( 8)); }); });
            describe("when value is 16", [&]{ it("should be 16", [&]{ AssertThat((16_bit).floor().bit(), Equals(16)); }); });
            describe("when value is 17", [&]{ it("should be 16", [&]{ AssertThat((17_bit).floor().bit(), Equals(16)); }); });
        });
        
        describe("#ceil()", [&]{
            describe("when value is 0" , [&]{ it("should be 0" , [&]{ AssertThat(( 0_bit).ceil().bit(), Equals( 0)); }); });
            describe("when value is 1" , [&]{ it("should be 8" , [&]{ AssertThat(( 1_bit).ceil().bit(), Equals( 8)); }); });
            describe("when value is 7" , [&]{ it("should be 8" , [&]{ AssertThat(( 7_bit).ceil().bit(), Equals( 8)); }); });
            describe("when value is 8" , [&]{ it("should be 8" , [&]{ AssertThat(( 8_bit).ceil().bit(), Equals( 8)); }); });
            describe("when value is 9" , [&]{ it("should be 16", [&]{ AssertThat(( 9_bit).ceil().bit(), Equals(16)); }); });
            describe("when value is 15", [&]{ it("should be 16", [&]{ AssertThat((15_bit).ceil().bit(), Equals(16)); }); });
            describe("when value is 16", [&]{ it("should be 16", [&]{ AssertThat((16_bit).ceil().bit(), Equals(16)); }); });
            describe("when value is 17", [&]{ it("should be 24", [&]{ AssertThat((17_bit).ceil().bit(), Equals(24)); }); });
        });
        
        describe("#max_value()", [&]{
            describe("when value is 0" , [&]{ it("should be 0"         , [&]{ AssertThat(( 0_bit).max_value(), Equals(         0)); }); });
            describe("when value is 10", [&]{ it("should be 1023"      , [&]{ AssertThat((10_bit).max_value(), Equals(      1023)); }); });
            describe("when value is 32", [&]{ it("should be 4294967295", [&]{ AssertThat((32_bit).max_value(), Equals(4294967295)); }); });
            describe("when value is 33", [&]{ it("should be 4294967295", [&]{ AssertThat((33_bit).max_value(), Equals(4294967295)); }); });
        });
        
        describe("#diff(bit_type target)", [&]{
            describe("when value is 7 and target is 5", [&]{ it("should be 2", [&]{ AssertThat((7_bit).diff(5_bit).bit(), Equals(2)); }); });
            describe("when value is 5 and target is 7", [&]{ it("should be 2", [&]{ AssertThat((5_bit).diff(7_bit).bit(), Equals(2)); }); });
        });
        
        describe("#addr(const T * addr)", [&]{
            it("should be `addr + #byte()`", [&]{
                bit_type bit(5);
                uint32_t * addr = 0x00;
                AssertThat(bit.addr(addr), Equals((uint8_t *)addr + bit.byte()));
            });
        });
    });
    
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

int main(int argc, char * argv[]) {
    return bandit::run(argc, argv);
}
