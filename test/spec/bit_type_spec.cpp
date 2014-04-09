#include <bandit/bandit.h>
#include <bitfield/bit_type.hpp>

namespace bitfield {
go_bandit([&]{
    using namespace bandit;
    
    describe("bit_type", [&]{
        describe("#floor()", [&]{
            describe("when value was 0" , [&]{ it("should be 0" , [&]{ AssertThat(( 0_bit).floor().bit(), Equals( 0)); }); });
            describe("when value was 1" , [&]{ it("should be 0" , [&]{ AssertThat(( 1_bit).floor().bit(), Equals( 0)); }); });
            describe("when value was 7" , [&]{ it("should be 0" , [&]{ AssertThat(( 7_bit).floor().bit(), Equals( 0)); }); });
            describe("when value was 8" , [&]{ it("should be 8" , [&]{ AssertThat(( 8_bit).floor().bit(), Equals( 8)); }); });
            describe("when value was 9" , [&]{ it("should be 8" , [&]{ AssertThat(( 9_bit).floor().bit(), Equals( 8)); }); });
            describe("when value was 15", [&]{ it("should be 8" , [&]{ AssertThat((15_bit).floor().bit(), Equals( 8)); }); });
            describe("when value was 16", [&]{ it("should be 16", [&]{ AssertThat((16_bit).floor().bit(), Equals(16)); }); });
            describe("when value was 17", [&]{ it("should be 16", [&]{ AssertThat((17_bit).floor().bit(), Equals(16)); }); });
        });
        
        describe("#ceil()", [&]{
            describe("when value was 0" , [&]{ it("should be 0" , [&]{ AssertThat(( 0_bit).ceil().bit(), Equals( 0)); }); });
            describe("when value was 1" , [&]{ it("should be 8" , [&]{ AssertThat(( 1_bit).ceil().bit(), Equals( 8)); }); });
            describe("when value was 7" , [&]{ it("should be 8" , [&]{ AssertThat(( 7_bit).ceil().bit(), Equals( 8)); }); });
            describe("when value was 8" , [&]{ it("should be 8" , [&]{ AssertThat(( 8_bit).ceil().bit(), Equals( 8)); }); });
            describe("when value was 9" , [&]{ it("should be 16", [&]{ AssertThat(( 9_bit).ceil().bit(), Equals(16)); }); });
            describe("when value was 15", [&]{ it("should be 16", [&]{ AssertThat((15_bit).ceil().bit(), Equals(16)); }); });
            describe("when value was 16", [&]{ it("should be 16", [&]{ AssertThat((16_bit).ceil().bit(), Equals(16)); }); });
            describe("when value was 17", [&]{ it("should be 24", [&]{ AssertThat((17_bit).ceil().bit(), Equals(24)); }); });
        });
        
        describe("#max_value()", [&]{
            describe("when value was 0" , [&]{ it("should be 0"         , [&]{ AssertThat(( 0_bit).max_value(), Equals(         0)); }); });
            describe("when value was 10", [&]{ it("should be 1023"      , [&]{ AssertThat((10_bit).max_value(), Equals(      1023)); }); });
            describe("when value was 32", [&]{ it("should be 4294967295", [&]{ AssertThat((32_bit).max_value(), Equals(4294967295)); }); });
            describe("when value was 33", [&]{ it("should be 4294967295", [&]{ AssertThat((33_bit).max_value(), Equals(4294967295)); }); });
        });
        
        describe("#add(bit_type target)", [&]{
            describe("when value was 2 and target was 3", [&]{ it("should be 5", [&]{ AssertThat((2_bit).add(3_bit).bit(), Equals(5)); }); });
        });
        
        describe("#diff(bit_type target)", [&]{
            describe("when value was 7 and target was 5", [&]{ it("should be 2", [&]{ AssertThat((7_bit).diff(5_bit).bit(), Equals(2)); }); });
            describe("when value was 5 and target was 7", [&]{ it("should be 2", [&]{ AssertThat((5_bit).diff(7_bit).bit(), Equals(2)); }); });
        });
        
        describe("#addr(const U * base_addr)", [&]{
            it("should be `base_addr + #byte()`", [&]{
                bit_type bit(5);
                uint32_t * base_addr = 0x00;
                AssertThat(bit.addr(base_addr), Equals((uint8_t *)base_addr + bit.byte()));
            });
        });
    });
});
}
