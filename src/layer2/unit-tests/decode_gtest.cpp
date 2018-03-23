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
 */
TEST (Decode, DecodeEthernet) {
    const uint8_t pkt [EthernetLen] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x10, 0x20, 0x08, 0x00};

    testing::internal::CaptureStdout();
    size_t l = layer2_decode(pkt);
    string s = testing::internal::GetCapturedStdout();

    string sVal = "Src Address: 00:11:22:33:44:55\nDst Address: 66:77:88:99:10:20\nEtherType:   0x0800 (ipv4)\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());
}
