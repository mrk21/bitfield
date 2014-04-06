bitfield
========

C++11 bitfield template library

Examples
========

Analyzing the IP header:

```c++
#include <bitfield/bitfield.hpp>
#include <bitfield/iostream.hpp>

// IP header
union ip_header {
    using version_type           =                    bitfield::bitfield< 4>;
    using ihl_type               =           version_type::next_bitfield< 4>;
    using dscp_type              =               ihl_type::next_bitfield< 6>;
    using ecn_type               =              dscp_type::next_bitfield< 2>;
    using total_length_type      =               ecn_type::next_bitfield<16>;
    using identification_type    =      total_length_type::next_bitfield<16>;
    using flags_type             =    identification_type::next_bitfield< 3>;
    using fragment_offset_type   =             flags_type::next_bitfield<13>;
    using time_to_live_type      =   fragment_offset_type::next_bitfield< 8>;
    using protocol_type          =      time_to_live_type::next_bitfield< 8>;
    using header_checksum_type   =          protocol_type::next_bitfield<16>;
    using source_ip_address_type =   header_checksum_type::next_bitfield<32>;
    using dest_ip_address_type   = source_ip_address_type::next_bitfield<32>;
    using options_type           =   dest_ip_address_type::next_bitfield<32>;
    using container_type = options_type::container_type;
    
    container_type container;
    
    version_type            version;
    ihl_type                ihl;
    dscp_type               dscp;
    ecn_type                ecn;
    total_length_type       total_length;
    identification_type     identification;
    flags_type              flags;
    fragment_offset_type    fragment_offset;
    time_to_live_type       time_to_live;
    protocol_type           protocol;
    header_checksum_type    header_checksum;
    source_ip_address_type  source_ip_address;
    dest_ip_address_type    dest_ip_address;
    options_type            options;
};

int main() {
    // packet
    ip_header packet{{{
        0x45, 0x00, 0x00, 0x30, 0x26, 0xd6, 0x40, 0x00,  0x80, 0x06, 0x58, 0x86, 0xc0, 0xa8, 0x01, 0x8f,
        0xd2, 0xe1, 0xe6, 0x52,
    }}};
    
    //== Get field == 
    // IP version: 4
    // total length: 48
    std::cout << "IP version: " << packet.version << std::endl;
    std::cout << "total length: " << packet.total_length << std::endl;
    
    //== Set field ==
    // TTL: 128
    // TTL: 127
    std::cout << "TTL: " << packet.time_to_live << std::endl;
    packet.time_to_live = packet.time_to_live - 1; // decrement TTL
    std::cout << "TTL: " << packet.time_to_live << std::endl;
    
    return 0;
}
```
