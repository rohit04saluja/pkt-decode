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
 * TEST the working of layer2 decode
 * ethernet packet
 */
TEST (Decode, DecodeEthernet) {
    const uint8_t pkt [EthernetLen] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x10, 0x20, 0x08, 0x00};

    testing::internal::CaptureStdout();
    size_t l = layer2_decode(pkt);
    string s = testing::internal::GetCapturedStdout();

    string sVal = "Src Address: 00:11:22:33:44:55\nDst Address: 66:77:88:99:10:20\nEtherType:   0x0800 (ipv4)\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());
    EXPECT_EQ (EthernetLen, l);
}

/*
 * @brief
 * TEST the working of layer2 decode for
 * single tagged packet
 */
TEST (Decode, DecodeEthVlanTagSingle) {
    uint8_t pkt [EthVlanTagSingleLen] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x10, 0x20, 0x81, 0x00, 0x32, 0x00, 0x08, 0x00};
    
    testing::internal::CaptureStdout();
    size_t l = layer2_decode(pkt);
    string s = testing::internal::GetCapturedStdout();

    string sVal = "Src Address: 00:11:22:33:44:55\nDst Address: 66:77:88:99:10:20\nTpid: 0x8100\nPcp:  1\nDei:  1\nVid:  0x200/512\nEtherType:   0x0800 (ipv4)\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());
    EXPECT_EQ(EthVlanTagSingleLen, l);

    pkt[MacAddrLen*2] = 0x82;

    testing::internal::CaptureStdout();
    l = layer2_decode(pkt);
    s = testing::internal::GetCapturedStdout();

    sVal = "Src Address: 00:11:22:33:44:55\nDst Address: 66:77:88:99:10:20\nEtherType:   0x8200 (unknown)\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());
    EXPECT_EQ(EthernetLen, l);
}
