#include <bandit/bandit.h>
#include <bitfield/util.hpp>
#include <bitfield/container/vector.hpp>
#include <bitfield/section/base.hpp>
#include <bitfield/section/list.hpp>
#include <vector>

namespace bitfield { namespace util {
    namespace hex_dump_traits_test {
        template<typename T>
        using std_vector = hex_dump_traits<std::vector<T>>;
        
        using section_base = hex_dump_traits<section::base<int,int,int>>;
        using section_list_iterator = hex_dump_traits<section::list<int,int,int>::iterator>;
    }
    
go_bandit([]{
    using namespace bandit;
    
    describe("util::hex_dump_traits<Container>::IS_SUPPORT", [&]{
        describe("when the Container was a std::vector<T>", [&]{
            describe("when the T was a double", [&]{
                 it("should be false", [&]{
                     AssertThat((bool)hex_dump_traits_test::std_vector<double>::IS_SUPPORT, Equals(false));
                 });
            });
            
            describe("when the T was an uint8_t", [&]{
                 it("should be true", [&]{
                     AssertThat((bool)hex_dump_traits_test::std_vector<uint8_t>::IS_SUPPORT, Equals(true));
                 });
            });
            
            describe("when the T was an int8_t", [&]{
                 it("should be false", [&]{
                     AssertThat((bool)hex_dump_traits_test::std_vector<int8_t>::IS_SUPPORT, Equals(false));
                 });
            });
        });
        
        describe("when the Container was a section::base<D,F,P>", [&]{
            it("should be true", [&]{
                AssertThat((bool)hex_dump_traits_test::section_base::IS_SUPPORT, Equals(true));
            });
        });
        
        describe("when the Container was a section::list<D,F,P>::iterator", [&]{
            it("should be true", [&]{
                AssertThat((bool)hex_dump_traits_test::section_list_iterator::IS_SUPPORT, Equals(true));
            });
        });
    });
    
    describe("util::hex_dump(const Container & container)", [&]{
        it("should be a hex dump", [&]{
            container::vector bytes{
                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x02, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x04, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x05, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x06, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x07, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x09, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x0A, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x0B, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x0C, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x0D, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x0E, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x0F, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                
                0x10, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x11, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x12, 0x01, 0x02, 0x03, 0x04, 0x05, 
            };
            
            std::string expected = "";
            expected += "0000 | 00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0010 | 01 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0020 | 02 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0030 | 03 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0040 | 04 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0050 | 05 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0060 | 06 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0070 | 07 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0080 | 08 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0090 | 09 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "00A0 | 0A 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "00B0 | 0B 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "00C0 | 0C 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "00D0 | 0D 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "00E0 | 0E 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "00F0 | 0F 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0100 | 10 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0110 | 11 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n";
            expected += "0120 | 12 01 02 03 04 05\n";
            
            AssertThat(hex_dump(bytes), Equals(expected));
        });
    });
});
}}
