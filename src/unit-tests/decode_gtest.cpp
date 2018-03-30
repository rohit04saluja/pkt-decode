/*
 * decode_gtest.cpp
 *
 * Created by Rohit Saluja on 3/23/2018.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <gtest/gtest.h>
#include "decode.hpp"
#include "ethernet.hpp"

using namespace std;

/*
 * @brief
 * TEST the working of decode
 * ethernet packet
 */
TEST (Decode, DecodeEthernet) {
    const uint8_t pkt [19] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x10, 0x20, 0x08, 0x00, 0x12, 0x34, 0x56, 0x78, 0x90};

    testing::internal::CaptureStdout();
    decode(pkt, 19);
    string s = testing::internal::GetCapturedStdout();

    string sVal;
    sVal += "Layer2:\n";
    sVal += "  Dst Address: 00:11:22:33:44:55\n";
    sVal += "  Src Address: 66:77:88:99:10:20\n";
    sVal += "  EtherType: 0x0800 (ipv4)\n";
    sVal += "Data: 0x12 0x34 0x56 0x78 0x90\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());
}

/*
 * @brief
 * TEST the working of layer2 decode for
 * single tagged packet
 */
TEST (Decode, DecodeEthVlanTagSingle) {
    const uint8_t pkt [23] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x10, 0x20, 0x81, 0x00, 0x32, 0x00, 0x08, 0x00, 0x12, 0x34, 0x56, 0x78, 0x90};
    
    testing::internal::CaptureStdout();
    decode(pkt, 23);
    string s = testing::internal::GetCapturedStdout();

    string sVal;
    sVal += "Layer2:\n";
    sVal += "  Dst Address: 00:11:22:33:44:55\n";
    sVal += "  Src Address: 66:77:88:99:10:20\n";
    sVal += "  Tpid: 0x8100\n";
    sVal += "  Pcp: 1\n";
    sVal += "  Dei: 1\n";
    sVal += "  Vid: 0x200/512\n";
    sVal += "  EtherType: 0x0800 (ipv4)\n";
    sVal += "Data: 0x12 0x34 0x56 0x78 0x90\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());
}

/*
 * @brief
 * TEST the working of layer2 decode for
 * single tagged packet
 */
TEST (Decode, DecodeIpv4) {
    const uint8_t pkt [50] = {0x00, 0x1C, 0x0F, 0x09, 0x00, 0x10, 0x00, 0x1C, 0x0F, 0x5C, 0xA2, 0x83, 0x81, 0x00, 0x00, 0xCA, 0x08, 0x00, 0x45, 0x00, 0x00, 0xDC, 0xD4, 0x31, 0x00, 0x00, 0xF5, 0x11, 0x17, 0xDF, 0x59, 0x2E, 0x65, 0x1F, 0xC4, 0x5F, 0x46, 0x53, 0x9F, 0x74, 0x00, 0x7B, 0x00, 0xC8, 0x00, 0x00, 0x17, 0x00, 0x03, 0x2A};
    
    testing::internal::CaptureStdout();
    decode(pkt, 50);
    string s = testing::internal::GetCapturedStdout();

    string sVal;
    sVal += "Layer2:\n";
    sVal += "  Dst Address: 00:1c:0f:09:00:10\n";
    sVal += "  Src Address: 00:1c:0f:5c:a2:83\n";
    sVal += "  Tpid: 0x8100\n";
    sVal += "  Pcp: 0\n";
    sVal += "  Dei: 0\n";
    sVal += "  Vid: 0x0ca/202\n";
    sVal += "  EtherType: 0x0800 (ipv4)\n";
    sVal += "Layer3:\n";
    sVal += "  Version: 4\n";
    sVal += "  Header Len: 5 (20B)\n";
    sVal += "  DSCP: 0\n";
    sVal += "  ECN: 0\n";
    sVal += "  Total Len: 220\n";
    sVal += "  Id: 54321\n";
    sVal += "  Flag: 0 (reserved)\n";
    sVal += "  Frag Offset: 0\n";
    sVal += "  TTL: 245\n";
    sVal += "  Protocol: 17 (udp)\n";
    sVal += "  Checksum: 0x17df\n";
    sVal += "  Source Ip: 89.46.101.31\n";
    sVal += "  Destination Ip: 196.95.70.83\n";
    sVal += "Data: 0x9f 0x74 0x00 0x7b 0x00 0xc8 0x00 0x00 0x17 0x00 0x03 0x2a\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());
}

