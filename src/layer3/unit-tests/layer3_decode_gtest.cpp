/*
 * layer3_decode_gtest.cpp
 *
 * Created by Rohit Saluja on 3/30/2018.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <gtest/gtest.h>
#include "layer3_decode.hpp"
#include "ipv4.hpp"

using namespace std;

/*
 * @brief
 * TEST the working of layer3 decode
 * IPv4 packet
 */
TEST (Layer3Decode, Layer3DecodeIpv4) {
    const uint8_t pkt[Ipv4MinLen] = {0x45, 0x00, 0x00, 0xdc, 0xd4, 0x31, 0x00, 0x00, 0xF5, 0x11, 0x17, 0xdf, 0x59, 0x2e, 0x65, 0x1f, 0xc4, 0x5f, 0x46, 0x53};

    testing::internal::CaptureStdout();
    size_t l = layer3_decode(pkt);
    string s = testing::internal::GetCapturedStdout();

    string sVal;
    sVal += "Layer3:\n";
    sVal += "  Version:        4\n";
    sVal += "  Header Len:     5 (20B)\n";
    sVal += "  DSCP:           0\n";
    sVal += "  ECN:            0\n";
    sVal += "  Total Len:      220\n";
    sVal += "  Id:             54321\n";
    sVal += "  Flag:           0 (reserved)\n";
    sVal += "  Frag Offset:    0\n";
    sVal += "  TTL:            245\n";
    sVal += "  Protocol:       17 (udp)\n";
    sVal += "  Checksum:       0x17df\n";
    sVal += "  Source Ip:      89.46.101.31\n";
    sVal += "  Destination Ip: 196.95.70.83\n";
    
    EXPECT_STREQ(s.c_str(), sVal.c_str());
    EXPECT_EQ (Ipv4MinLen/sizeof(uint32_t), l);
}
