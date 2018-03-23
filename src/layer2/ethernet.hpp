/*
 * ethernet.hpp
 *
 * Created by Rohit Saluja on 3/22/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_

#include <iostream>
#include <cstdint>

using namespace std;

/*
 * @brief
 * Lenghts of different components of layer2 header
 */
#define MacAddrLen      6
#define EtherTypeLen    2
#define EthernetLen     MacAddrLen * 2 + EtherTypeLen

/*
 * @brief
 * Class for mac address of packet
 */
class MacAddr {
    private:
    uint8_t addr[MacAddrLen];

    public:
    MacAddr (void);
    MacAddr (uint8_t const * pkt);
    uint8_t const * Addr (void) const;
    friend ostream & operator<< (ostream &output, MacAddr const &addr);
    friend bool const operator== (MacAddr const &lhs, MacAddr const &rhs);
    friend bool const operator!= (MacAddr const &lhs, MacAddr const &rhs);
};

/*
 * @brief
 * Class for ether type
 */
class EtherType {
    private:
    uint16_t et;

    public:
    EtherType (void);
    EtherType (const uint16_t val);
    EtherType (const uint8_t * pkt);
    uint16_t const Et (void) const;
    string const EtName (void) const;
    friend bool const operator== (EtherType const &lhs, EtherType const &rhs);
    friend bool const operator!= (EtherType const &lhs, EtherType const &rhs);
    friend ostream & operator<< (ostream &output, EtherType const &et);
};

/*
 * @brief
 * Class for ethernet packet
 */
class Ethernet {
    private:
    MacAddr srcAddr;
    MacAddr dstAddr;
    EtherType et;

    public:
    Ethernet (void);
    Ethernet (const uint8_t * pkt);
    MacAddr const & SrcAddr (void) const;
    MacAddr const & DstAddr (void) const;
    EtherType const & Et (void) const;
    void print (const uint8_t ls=0) const;
    friend bool const operator== (Ethernet const &lhs, Ethernet const &rhs);
    friend bool const operator!= (Ethernet const &lhs, Ethernet const &rhs);
};

/*
 * @brief
 * Different ether types
 */
#define ETH_TYPE_IPV4       0x0800
#define ETH_TYPE_VLAN       0x8100

#endif  // ETHERNET_H_
