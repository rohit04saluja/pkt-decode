/*
 * ethernet.cpp
 *
 * Created by Rohit Saluja on 3/22/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <ethernet.hpp>
#include <iomanip>
#include <sstream>

using namespace std;

/*
 * @brief
 * Default constructor for class
 * inititalize the address to 0
 */
MacAddr::MacAddr (void) {
    memset (addr, 0, MacAddrLen);
}

/*
 * @brief
 * Constructor to initialize the
 * address from given bye stream
 *
 * @param[in]
 * pkt     top of the address stream
 */
MacAddr::MacAddr (uint8_t const * pkt) {
    memcpy (addr, pkt, MacAddrLen);
}

/*
 * @brief
 * Method to get a pointer to start of address
 *
 * @return
 * pointer to start of address
 */
uint8_t const * MacAddr::Addr (void) const {
    return addr;
}

/*
 * @brief
 * operator<< overloaded for printing the address
 *
 * @param[in]
 * output   output stream
 * @paramp[in]
 * addr     mac address class
 *
 * @return
 * output stream with the prints
 */
ostream & operator<< (ostream &output, MacAddr const &addr) {
    for (int i=0; i<MacAddrLen; i++) {
        output << (i!=0 ? ":" : "");
        output << hex << setfill('0') << setw(2) << +addr.addr[i];
    }
    return output;
}

/*
 * @brief
 * operator== overloaded to tell if
 * two addresses are the same
 *
 * @param[in]
 * lhs      left side of the operator
 * @param[in]
 * rhs      right side of the operator
 *
 * @return
 * true if all the bytes are equal
 */
bool const operator== (MacAddr const &lhs, MacAddr const &rhs) {
    bool ret = true;
    for (int i=0; i<MacAddrLen; i++) {
        if (lhs.addr[i] != rhs.addr[i]) {
            ret = false;
            break;
        }
    }
    return ret;
}

/*
 * @brief
 * operator!= overloaded to tell if 
 * two address are not the same
 *
 * @param[in]
 * lhs      left side of the operator
 * @param[in]
 * rhs      right side of the operator
 *
 * @return
 * true if operator== is false
 */
bool const operator!= (MacAddr const &lhs, MacAddr const &rhs) {
    return !(lhs == rhs);
}


/*
 * @brief
 * Default constructor for class
 * initializa ethertype to 0
 */
EtherType::EtherType (void) {
    et = 0;
}

/*
 * @brief
 * Constructor to initializa
 * ethertype from given value
 *
 * @param[in]
 * val      value of ethertype
 */
EtherType::EtherType (const uint16_t val) {
    et = ntohs(val);
}

/*
 * @brief
 * Constructor to initializa
 * etherype from packet pointer
 *
 * @param[in]
 * pkt      pointer to ethertype in packet
 */
EtherType::EtherType (const uint8_t * pkt) {
    et = ntohs(*((uint16_t *) pkt));
}

/*
 * @brief
 * Method to get the ethertype
 *
 * @return
 * ethertype value
 */
uint16_t const EtherType::Et (void) const {
    return et;
}

/*
 * @brief
 * Method to get the name of ethertype
 *
 * @return
 * ethertype name
 */
string const EtherType::EtName (void) const {
    switch (et) {
        case ETH_TYPE_IPV4:
            return "ipv4";
        case ETH_TYPE_VLAN:
            return "vlan";
        default:
            return "unknown";
    }
}

/*
 * @brief
 * operator<< overloaded to print hex of ethertype
 *
 * @param[in]
 * output       output stream
 * @param[in]
 * et           ether tyoe class
 *
 * @return
 * output stream with the print
 */
ostream & operator<< (ostream &output, EtherType const &et) {
    output << "0x" << setfill('0') << setw(4) << hex << et.et;
    return output;
}

/*
 * @brief
 * operator== overloaded to tell if ethertypes are equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if both values are equal
 */
bool const operator== (EtherType const &lhs, EtherType const &rhs) {
    return (lhs.et == rhs.et);
}

/*
 * @brief
 * operator!= overloaded to tell if ethertypes are not equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if both values are not equal
 */
bool const operator!= (EtherType const &lhs, EtherType const &rhs) {
    return (lhs.et != rhs.et);
}


/*
 * @brief
 * Default constructor for class
 * initialize header to 0
 */
EthVlanTag::EthVlanTag (void) {
    tpid = EtherType();
    pcp = 0;
    dei = 0;
    vid = 0;
}

/*
 * @brief
 * Initialization constructor for class
 * initializa the pkt header
 *
 * @param[in]
 * pkt      pointer to packet
 */
EthVlanTag::EthVlanTag (const uint8_t * pkt) {
    tpid = EtherType(pkt);
    pcp = 0x7 & (*(pkt+EtherTypeLen) >> 5);
    dei = 0x1 & (*(pkt+EtherTypeLen) >> 4);
    vid = 0xfff & ntohs(*((uint16_t *) (pkt+EtherTypeLen)));
}

/*
 * @brief
 * Method to get tpid
 */
EtherType const EthVlanTag::Tpid (void) const {
    return tpid;
}

/*
 * @brief
 * Method to get pcp
 */
uint8_t const EthVlanTag::Pcp (void) const {
    return pcp;
}

/*
 * @brief
 * Method to get dei
 */
uint8_t const EthVlanTag::Dei (void) const {
    return dei;
}

/*
 * @brief
 * Method to get vid
 */
uint16_t const EthVlanTag::Vid (void) const {
    return vid;
}

/*
 * @brief
 * Method to print the Vlang to the consold
 *
 * @param[in]
 * ls       number of leading spaces
 */
void EthVlanTag::print (const uint8_t ls) const {
    cout << string(ls, ' ') << "Tpid: " << tpid << endl;
    cout << string(ls, ' ') << "Pcp:  " << +pcp << endl;
    cout << string(ls, ' ') << "Dei:  " << +dei << endl;
    cout << string(ls, ' ') << "Vid:  0x" << setfill('0') << setw(3) << hex << vid << "/" << dec << vid << endl;
}

/*
 * @brief
 * operator== overloaded to tell if tags are equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if all the fields are equal
 */
bool const operator== (EthVlanTag const &lhs, EthVlanTag const &rhs) {
    if (lhs.tpid == rhs.tpid &&
        lhs.pcp == rhs.pcp &&
        lhs.dei == rhs.dei &&
        lhs.vid == rhs.vid) {
        return true;
    }
    return false;
}

/*
 * @brief
 * operator!= overloaded to tell if tags are not equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if operator== is false
 */
bool const operator!= (EthVlanTag const &lhs, EthVlanTag const &rhs) {
    return !(lhs == rhs);
}


/*
 * @brief
 * Default constructor for class
 * initialize packet to 0
 */
Ethernet::Ethernet (void) {
    srcAddr = MacAddr();
    dstAddr = MacAddr();
    et = EtherType();
}

/*
 * @brief
 * Initialization constructor for class
 * initialize the pkt header from pkt
 *
 * @param[in]
 * pkt      pointer to start of packet
 */
Ethernet::Ethernet (const uint8_t * pkt) {
    srcAddr = MacAddr(pkt);
    dstAddr = MacAddr(pkt + MacAddrLen);
    et = EtherType(pkt + MacAddrLen * 2);
}

/*
 * @brief
 * Method to get the src address
 */
MacAddr const & Ethernet::SrcAddr (void) const {
    return srcAddr;
}

/*
 * @brief
 * Method to get the dst address
 */
MacAddr const & Ethernet::DstAddr (void) const {
    return dstAddr;
}

/*
 * @brief
 * Method to get the ethertype
 */
EtherType const & Ethernet::Et (void) const {
    return et;
}

/*
 * @brief
 * Print the header with values
 *
 * @param[in]
 * ls       leading spaces that need to be given
 */
void Ethernet::print (const uint8_t ls) const {
    cout << string(ls, ' ') << "Src Address: " << srcAddr << endl;
    cout << string(ls, ' ') << "Dst Address: " << dstAddr << endl;
    cout << string(ls, ' ') << "EtherType:   " << et << " (" << et.EtName() << ")" << endl;
}

/*
 * @brief
 * operator== overloaded to tell
 * if Ethernet headers are same
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true is all members are equal
 */
bool const operator== (Ethernet const &lhs, Ethernet const &rhs) {
    if (lhs.SrcAddr() == rhs.SrcAddr() &&
        lhs.DstAddr() == rhs.DstAddr() &&
        lhs.Et() == rhs.Et()) {
        return true;
    }
    return false;
}

/*
 * @brief
 * operator== overloaded to tell
 * if Ethernet headers are same
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true is all members are equal
 */
bool const operator!= (Ethernet const &lhs, Ethernet const &rhs) {
    if (lhs.SrcAddr() != rhs.SrcAddr() ||
        lhs.DstAddr() != rhs.DstAddr() ||
        lhs.Et() != rhs.Et()) {
        return true;
    }
    return false;
}
