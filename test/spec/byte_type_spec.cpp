#include <bandit/bandit.h>
#include <bitfield/byte_type.hpp>

namespace bitfield {
go_bandit([&]{
    using namespace bandit;
    
    describe("byte_type", [&]{
        describe("#max_value()", [&]{
            describe("when value was 0", [&]{ it("should be 0"         , [&]{ AssertThat((0_byte).max_value(), Equals(         0)); }); });
            describe("when value was 1", [&]{ it("should be 255"       , [&]{ AssertThat((1_byte).max_value(), Equals(       255)); }); });
            describe("when value was 4", [&]{ it("should be 4294967295", [&]{ AssertThat((4_byte).max_value(), Equals(4294967295)); }); });
            describe("when value was 5", [&]{ it("should be 4294967295", [&]{ AssertThat((5_byte).max_value(), Equals(4294967295)); }); });
        });
        
        describe("#add(byte_type target)", [&]{
            describe("when value was 2 and target was 3", [&]{ it("should be 5", [&]{ AssertThat((2_byte).add(3_byte).byte(), Equals(5)); }); });
        });
        
        describe("#diff(byte_type target)", [&]{
            describe("when value was 7 and target was 5", [&]{ it("should be 2", [&]{ AssertThat((7_byte).diff(5_byte).byte(), Equals(2)); }); });
            describe("when value was 5 and target was 7", [&]{ it("should be 2", [&]{ AssertThat((5_byte).diff(7_byte).byte(), Equals(2)); }); });
        });
        
        describe("#addr(const U * base_addr)", [&]{
            it("should be `base_addr + #byte()`", [&]{
                byte_type byte(5);
                uint32_t * base_addr = 0x00;
                AssertThat(byte.addr(base_addr) == ((uint8_t *)base_addr + byte.byte()), Equals(true));
            });
        });
    });
});
}
