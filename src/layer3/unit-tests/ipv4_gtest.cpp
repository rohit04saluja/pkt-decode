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

/*
 * @brief
 * TEST normal working of L3Proto
 */
TEST(L3Proto, L3ProtoInit) {
    L3Proto proto(17);
    ostringstream os;
    os << proto;
    EXPECT_STREQ("17", os.str().c_str());
    EXPECT_STREQ("udp", proto.Name().c_str());
}

/*
 * @brief
 * TEST normal working of Ipv4Flag
 */
TEST(Ipv4Flag, Ipv4FlagInit) {
   Ipv4Flag flag1(3), flag2(1);
   
   EXPECT_STREQ(flag1.Name().c_str(), "unknown");
   EXPECT_STREQ(flag2.Name().c_str(), "df");

   EXPECT_NE(flag1, flag2);
}

/*
 * @brief
 * TEST normal work of IPv4
 */
TEST(Ipv4, Ipv4Init) {
    const uint8_t pkt[Ipv4MinLen] = {0x45, 0x00, 0x00, 0xdc, 0xd4, 0x31, 0x00, 0x00, 0xF5, 0x11, 0x17, 0xdf, 0x59, 0x2e, 0x65, 0x1f, 0xc4, 0x5f, 0x46, 0x53};
    Ipv4 head(pkt);

    EXPECT_EQ(0, memcmp(pkt, head.HexDump(), Ipv4MinLen));

    testing::internal::CaptureStdout();
    head.print();
    string s = testing::internal::GetCapturedStdout();
    string sVal;
    sVal += "Version: 4\n";
    sVal += "Header Len: 5 (20B)\n";
    sVal += "DSCP: 0\n";
    sVal += "ECN: 0\n";
    sVal += "Total Len: 220\n";
    sVal += "Id: 54321\n";
    sVal += "Flag: 0 (reserved)\n";
    sVal += "Frag Offset: 0\n";
    sVal += "TTL: 245\n";
    sVal += "Protocol: 17 (udp)\n";
    sVal += "Checksum: 0x17df\n";
    sVal += "Source Ip: 89.46.101.31\n";
    sVal += "Destination Ip: 196.95.70.83\n";

    EXPECT_STREQ(s.c_str(), sVal.c_str());
}

/*
 * @brief
 * TEST equality of Ipv4 header
 */
TEST (Ipv4, Ipv4Eq) {
    const uint8_t pkt1[Ipv4MinLen] = {0x45, 0x00, 0x00, 0xdc, 0xd4, 0x31, 0x00, 0x00, 0xF5, 0x11, 0x17, 0xdf, 0x59, 0x2e, 0x65, 0x1f, 0xc4, 0x5f, 0x46, 0x53};
    const uint8_t pkt2[Ipv4MinLen] = {0x45, 0x00, 0x00, 0xdc, 0xd4, 0x31, 0x00, 0x00, 0xF5, 0x11, 0x17, 0xdf, 0x59, 0x2e, 0x65, 0x1f, 0xc4, 0x5f, 0x46, 0x50};
    Ipv4 head1(pkt1);
    Ipv4 head2(pkt2);
    
    EXPECT_NE(head1, head2);
}

/*
 * @brief
 * TEST validity of Ipv4 header
 */
TEST (Ipv4, Ipv4Valid) {
    uint8_t pkt[Ipv4MinLen] = {0x45, 0x00, 0x00, 0xdc, 0xd4, 0x31, 0x00, 0x00, 0xF5, 0x11, 0x17, 0xdf, 0x59, 0x2e, 0x65, 0x1f, 0xc4, 0x5f, 0x46, 0x53};
    Ipv4 head(pkt);
    EXPECT_TRUE(head.isValid());
    pkt[0] = 0x60;
    head = Ipv4(pkt);
    EXPECT_FALSE(head.isValid());
}
