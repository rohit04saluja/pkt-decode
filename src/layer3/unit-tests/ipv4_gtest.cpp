/*
 * ipv4_gtest.cpp
 *
 * Created by Rohit Saluja on 3/24/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <gtest/gtest.h>
#include <ipv4.hpp>

using namespace std;

/*
 * @brief
 * TEST normal working of Ipv4Addr
 */
TEST(Ipv4Addr, Ipv4AddrInit) {
    const uint8_t pkt[Ipv4AddrLen] = {192, 168, 0, 1};
    Ipv4Addr ipaddr(pkt);

    EXPECT_EQ(0, memcmp(ipaddr.Addr(), pkt, Ipv4AddrLen));

    ostringstream os;
    os << ipaddr;
    EXPECT_STREQ("192.168.0.1", os.str().c_str());
}

/*
 * @brief
 * TEST equality of Ipv4Addr
 */
TEST(Ipv4Addr, Ipv4AddrEq) {
    const uint8_t pkt1[Ipv4AddrLen] = {192, 168, 0, 1};
    const uint8_t pkt2[Ipv4AddrLen] = {192, 168, 0, 2};
    EXPECT_NE(Ipv4Addr(pkt1), Ipv4Addr(pkt2));
}
