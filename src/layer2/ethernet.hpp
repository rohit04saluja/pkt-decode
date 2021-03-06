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
 * Lenghts of different components of ethernet header
 */
#define MacAddrLen              6
#define EtherTypeLen            2
#define EthVlanTagLen           4
#define EthernetLen             MacAddrLen * 2 + EtherTypeLen
#define EthVlanTagSingleLen     EthernetLen + EthVlanTagLen
#define EthVlanTagDoubleLen     EthernetLen + EthVlanTagLen * 2

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
 * Class for vlang tag
 */
class EthVlanTag {
    private:
    EtherType tpid;
    uint8_t pcp:3;
    uint8_t dei:1;
    uint16_t vid:12;

    public:
    EthVlanTag (void);
    EthVlanTag (const uint8_t * pkt);
    EtherType const Tpid (void) const;
    uint8_t const Pcp (void) const;
    uint8_t const Dei (void) const;
    uint16_t const Vid (void) const;
    void print (const uint8_t ls=0) const;
    friend bool const operator== (EthVlanTag const &lhs, EthVlanTag const &rhs);
    friend bool const operator!= (EthVlanTag const &lhs, EthVlanTag const &rhs);
};

/*
 * @brief
 * Class for ethernet packet
 */
class Ethernet {
    protected:
    MacAddr dstAddr;
    MacAddr srcAddr;
    EtherType et;

    public:
    Ethernet (void);
    Ethernet (const uint8_t * pkt);
    MacAddr const & DstAddr (void) const;
    MacAddr const & SrcAddr (void) const;
    EtherType const & Et (void) const;
    virtual void print (const uint8_t ls=0) const;
    friend bool const operator== (Ethernet const &lhs, Ethernet const &rhs);
    friend bool const operator!= (Ethernet const &lhs, Ethernet const &rhs);
};

/*
 * @brief
 * Class for ethernet single tagged packet
 */
class EthVlanTagSingle : public Ethernet {
    protected:
    EthVlanTag vlan;

    public:
    EthVlanTagSingle (void);
    EthVlanTagSingle (const uint8_t * pkt);
    EthVlanTag const & Vlan (void) const;
    virtual void print (const uint8_t ls=0) const;
    bool const isValid (void) const;
    friend bool const operator== (EthVlanTagSingle const &lhs, EthVlanTagSingle const &rhs);
    friend bool const operator!= (EthVlanTagSingle const &lhs, EthVlanTagSingle const &rhs);
};

/*
 * @brief
 * Class for thernet double tagged packet
 */
class EthVlanTagDouble : public Ethernet {
    protected:
    EthVlanTag vlan1;
    EthVlanTag vlan2;

    public:
    EthVlanTagDouble (void);
    EthVlanTagDouble (const uint8_t * pkt);
    EthVlanTag const & Vlan1 (void) const;
    EthVlanTag const & Vlan2 (void) const;
    virtual void print (const uint8_t ls=0) const;
    bool const isValid (void) const;
    friend bool const operator== (EthVlanTagDouble const &lhs, EthVlanTagDouble const &rhs);
    friend bool const operator!= (EthVlanTagDouble const &lhs, EthVlanTagDouble const &rhs);
};

/*
 * @brief
 * Different ether types
 */
#define ETH_TYPE_IPV4       0x0800
#define ETH_TYPE_VLAN       0x8100

#endif  // ETHERNET_H_
