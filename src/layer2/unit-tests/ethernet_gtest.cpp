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

    ostringstream os;
    os << addr;
    EXPECT_STREQ("00:00:00:00:00:00", os.str().c_str());
}

/*
 * @brief
 * Test to check the working of initialization constructor
 */
TEST (MacAddr, MacAddrInit) {
    uint8_t pkt [MacAddrLen] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
    MacAddr addr(pkt);

    EXPECT_EQ(MacAddr(pkt), addr);

    ostringstream os;
    os << addr;
    EXPECT_STREQ("00:11:22:33:44:55", os.str().c_str());
}

/*
 * @brief
 * Test to check equality of MacAddr
 */
TEST (MacAddr, MacAddrNotEq) {
    uint8_t pkt1 [MacAddrLen] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    uint8_t pkt2 [MacAddrLen] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x55};

    EXPECT_NE (MacAddr(pkt1), MacAddr(pkt2));
}

/*
 * @brief
 * Test to check the working of default construct
 */
TEST (EtherType, EtherTypeDefault) {
    EtherType eth;

    EXPECT_EQ(EtherType(0), eth);

    ostringstream os;
    os << eth;
    EXPECT_STREQ("0x0000", os.str().c_str());
}

/*
 * @brief
 * Test to check the working of initialization constructor
 */
TEST (EtherType, EtherTypeInit) {
    uint8_t pkt [EtherTypeLen] = {0x08, 0x00};
    EtherType eth(*pkt);

    EXPECT_EQ(EtherType(*pkt), eth);

    ostringstream os;
    os << eth;
    EXPECT_STREQ("0x0800", os.str().c_str());
}

/*
 * @brief
 * Test to check if ether types are not equal
 */
TEST (EtherType, EtherTypeNotEq) {
    EXPECT_NE(EtherType(0x0800), EtherType(0x0801));
}

/*
 * @brief
 * Test to check normal working
 */
TEST (Ethernet, EthernetInit) {
    uint8_t pkt[EthernetLen] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x08, 0x00};
    Ethernet eth (pkt);
    
    const MacAddr srcAddr = eth.getSrcAddr();
    const MacAddr dstAddr = eth.getDstAddr();
    const EtherType ethT = eth.getEt();

    EXPECT_EQ(MacAddr(pkt), srcAddr);
    EXPECT_EQ(MacAddr(pkt+MacAddrLen), dstAddr);
    EXPECT_EQ(EtherType(*(pkt+MacAddrLen*2)), ethT);
    EXPECT_EQ(Ethernet(pkt), eth);

    testing::internal::CaptureStdout();
    eth.print(0);
    string s = testing::internal::GetCapturedStdout();

    string sVal = "Src Address: 11:22:33:44:55:66\nDst Address: 55:44:33:22:11:00\nEtherType:   0x0800\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());

    testing::internal::CaptureStdout();
    eth.print(4);
    s = testing::internal::GetCapturedStdout();

    sVal = "    Src Address: 11:22:33:44:55:66\n    Dst Address: 55:44:33:22:11:00\n    EtherType:   0x0800\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());
}

/*
 * @brief
 * Test to check headers being not equal
 */
TEST (Ethernet, EthernetNotEq) {
    uint8_t pkt1[EthernetLen] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x08, 0x00};
    uint8_t pkt2[EthernetLen] = {0x11, 0x22, 0x33, 0x44, 0x54, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x08, 0x00};
    EXPECT_NE(Ethernet(pkt1), Ethernet(pkt2));
}
