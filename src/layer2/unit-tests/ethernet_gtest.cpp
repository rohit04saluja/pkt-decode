/*
 * ethernet_gtest.cpp
 *
 * Created by Rohit Saluja on 3/22/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <gtest/gtest.h>
#include <ethernet.hpp>

using namespace std;

/*
 * @brief
 * Test to check the working of default constructor
 */
TEST (MacAddr, MacAddrDefault) {
    MacAddr addr;
    const uint8_t * out = addr.getAddr();

    for (int i=0; i<MacAddrLen; i++) {
        EXPECT_EQ(0, out[i]);
    }

    ostringstream os;
    os << addr;
    EXPECT_STREQ("00:00:00:00:00:00", os.str().c_str());
}

TEST (MacAddr, MacAddrInit) {
    uint8_t pkt [MacAddrLen] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
    MacAddr addr(pkt);
    const uint8_t * out = addr.getAddr();

    for (int i=0; i<MacAddrLen; i++) {
        EXPECT_EQ(pkt[i], out[i]);
    }
}
