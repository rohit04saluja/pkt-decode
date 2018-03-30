/*
 * ipv6_gtest.cpp
 *
 * Created by Rohit Saluja on 3/30/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <gtest/gtest.h>
#include <ipv6.hpp>

using namespace std;

/*
 * @brief
 * TEST normal working of Ipv6Addr
 */
TEST(Ipv6Addr, Ipv6AddrInit) {
    const uint8_t pkt[Ipv6AddrLen] = {0x20, 0x01, 0x0d, 0xb8, 0x85, 0xa3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x34};
    Ipv6Addr ipaddr(pkt);

    EXPECT_EQ(0, memcmp(ipaddr.Addr(), pkt, Ipv6AddrLen));

    ostringstream os;
    os << ipaddr;
    EXPECT_STREQ("2001:db8:85a3::7334", os.str().c_str());
}

/*
 * @brief
 * TEST equality of Ipv6Addr
 */
TEST(Ipv6Addr, Ipv6AddrEq) {
    const uint8_t pkt1[Ipv6AddrLen] = {0x20, 0x01, 0x0d, 0xb8, 0x85, 0xa1, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x2e, 0x03, 0x70, 0x73, 0x34};
    const uint8_t pkt2[Ipv6AddrLen] = {0x20, 0x01, 0x0d, 0xb8, 0x85, 0xa3, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x2e, 0x03, 0x70, 0x73, 0x34};
    EXPECT_NE(Ipv6Addr(pkt1), Ipv6Addr(pkt2));
}
