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

    EXPECT_EQ(0, memcmp(addr.Addr(), pkt, MacAddrLen));

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

    ostringstream os;
    os << eth;
    EXPECT_STREQ("0x0000", os.str().c_str());
}

/*
 * @brief
 * Test to check the working of initialization constructor
 */
TEST (EtherType, EtherTypeInit) {
    uint8_t pkt [EtherTypeLen] = {0x12, 0x34};
    EtherType eth(pkt);
    ostringstream os;

    EXPECT_EQ(eth.Et(), 0x1234);
    os << eth;
    EXPECT_STREQ("0x1234", os.str().c_str());
}

/*
 * @brief
 * Test to check if ether types are not equal
 */
TEST (EtherType, EtherTypeEq) {
    EXPECT_EQ(EtherType(0x1234), EtherType(0x1234));
    EXPECT_NE(EtherType(0x0800), EtherType(0x0801));
}

/*
 * @brief
 * Test to check normal working of EthVlanTag
 */
TEST (EthVlanTag, EthVlanTagInit) {
    uint8_t pkt[EthVlanTagLen] = {0x12, 0x34, 0x56, 0x78};
    EthVlanTag eth (pkt);

    EXPECT_EQ(eth.Tpid().Et(), 0x1234);
    EXPECT_EQ(eth.Pcp(), 0x2);
    EXPECT_EQ(eth.Dei(), 0x1);
    EXPECT_EQ(eth.Vid(), 0x678);

    testing::internal::CaptureStdout();
    eth.print();
    string s = testing::internal::GetCapturedStdout();

    string sVal = "Tpid: 0x1234\nPcp: 2\nDei: 1\nVid: 0x678/1656\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());

    testing::internal::CaptureStdout();
    eth.print(4);
    s = testing::internal::GetCapturedStdout();

    sVal = "    Tpid: 0x1234\n    Pcp: 2\n    Dei: 1\n    Vid: 0x678/1656\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());
}

/*
 * @brief
 * Test to check if eth vlan tags are not equal
 */
TEST(EthVlanTag, EthVlanTagEq) {
    uint8_t pkt1[EthVlanTagLen] = {0x12, 0x34, 0x56, 0x78};
    uint8_t pkt2[EthVlanTagLen] = {0x12, 0x34, 0x56, 0x79};
    EXPECT_EQ(EthVlanTag(pkt1), EthVlanTag(pkt1));
    EXPECT_NE(EthVlanTag(pkt1), EthVlanTag(pkt2));
}

/*
 * @brief
 * Test to check normal working of Ethernet
 */
TEST (Ethernet, EthernetInit) {
    uint8_t pkt[EthernetLen] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x08, 0x00};
    Ethernet eth (pkt);
    
    const MacAddr dstAddr = eth.DstAddr();
    const MacAddr srcAddr = eth.SrcAddr();
    const EtherType ethT = eth.Et();

    EXPECT_EQ(MacAddr(pkt), dstAddr);
    EXPECT_EQ(MacAddr(pkt+MacAddrLen), srcAddr);
    EXPECT_EQ(EtherType(*(pkt+MacAddrLen*2)), ethT);
    EXPECT_EQ(Ethernet(pkt), eth);

    testing::internal::CaptureStdout();
    eth.print(0);
    string s = testing::internal::GetCapturedStdout();

    string sVal = "Dst Address: 11:22:33:44:55:66\nSrc Address: 55:44:33:22:11:00\nEtherType: 0x0800 (ipv4)\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());

    testing::internal::CaptureStdout();
    eth.print(4);
    s = testing::internal::GetCapturedStdout();

    sVal = "    Dst Address: 11:22:33:44:55:66\n    Src Address: 55:44:33:22:11:00\n    EtherType: 0x0800 (ipv4)\n";
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

/*
 * @brief
 * Test to check normal working of EthVlanTagSingle
 */
TEST (EthVlanTagSingle, EthVlanTagSingleInit) {
    uint8_t pkt[EthVlanTagSingleLen] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x81, 0x00, 0x32, 0x00, 0x08, 0x00};
    EthVlanTagSingle eth (pkt);
    
    const MacAddr dstAddr = eth.DstAddr();
    const MacAddr srcAddr = eth.SrcAddr();
    const EthVlanTag tag = eth.Vlan();
    const EtherType ethT = eth.Et();

    EXPECT_EQ(MacAddr(pkt), dstAddr);
    EXPECT_EQ(MacAddr(pkt+MacAddrLen), srcAddr);
    EXPECT_EQ(EthVlanTag(pkt+MacAddrLen*2), tag);
    EXPECT_EQ(EtherType((pkt+MacAddrLen*2+EthVlanTagLen)), ethT);
    EXPECT_EQ(EthVlanTagSingle(pkt), eth);

    testing::internal::CaptureStdout();
    eth.print(0);
    string s = testing::internal::GetCapturedStdout();

    string sVal = "Dst Address: 11:22:33:44:55:66\nSrc Address: 55:44:33:22:11:00\nTpid: 0x8100\nPcp: 1\nDei: 1\nVid: 0x200/512\nEtherType: 0x0800 (ipv4)\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());

    testing::internal::CaptureStdout();
    eth.print(4);
    s = testing::internal::GetCapturedStdout();

    sVal = "    Dst Address: 11:22:33:44:55:66\n    Src Address: 55:44:33:22:11:00\n    Tpid: 0x8100\n    Pcp: 1\n    Dei: 1\n    Vid: 0x200/512\n    EtherType: 0x0800 (ipv4)\n";
    EXPECT_STREQ(s.c_str(), sVal.c_str());

    pkt[MacAddrLen*2 + 1] = 0x01;
}

/*
 * @brief
 * Test to check headers being not equal
 */
TEST (EthVlanTagSingle, EthVlanTagSingleEq) {
    uint8_t pkt1[EthVlanTagSingleLen] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x81, 0x00, 0x32, 0x00, 0x08, 0x00};
    uint8_t pkt2[EthVlanTagSingleLen] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x81, 0x00, 0x31, 0x00, 0x08, 0x00};
    EXPECT_NE(EthVlanTagSingle(pkt1), EthVlanTagSingle(pkt2));
}

/*
 * @brief
 * TEST to check validity of Single tagged packet
 */
TEST (EthVlanTagSingle, EthVlanTagSingleValid) {
    uint8_t pkt[EthVlanTagSingleLen] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x81, 0x00, 0x32, 0x00, 0x08, 0x00};
    EXPECT_TRUE(EthVlanTagSingle(pkt).isValid());
    pkt[MacAddrLen*2] = 0x82;
    EXPECT_FALSE(EthVlanTagSingle(pkt).isValid());
}
