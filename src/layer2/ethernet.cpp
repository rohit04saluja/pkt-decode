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
uint8_t const * MacAddr::getAddr (void) const {
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
 * Method to get the ethertype
 *
 * @return
 * ethertype value
 */
uint16_t const EtherType::getEt (void) const {
    return et;
}

/*
 * @brief
 * Method to get the name of ethertype
 *
 * @return
 * ethertype name
 */
string const EtherType::getName (void) const {
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
MacAddr const & Ethernet::getSrcAddr (void) const {
    return srcAddr;
}

/*
 * @brief
 * Method to get the dst address
 */
MacAddr const & Ethernet::getDstAddr (void) const {
    return dstAddr;
}

/*
 * @brief
 * Method to get the ethertype
 */
EtherType const & Ethernet::getEt (void) const {
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
    cout << string(ls, ' ') << "EtherType:   " << et << " (" << et.getName() << ")" << endl;
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
    if (lhs.getSrcAddr() == rhs.getSrcAddr() &&
        lhs.getDstAddr() == rhs.getDstAddr() &&
        lhs.getEt() == rhs.getEt()) {
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
    if (lhs.getSrcAddr() != rhs.getSrcAddr() ||
        lhs.getDstAddr() != rhs.getDstAddr() ||
        lhs.getEt() != rhs.getEt()) {
        return true;
    }
    return false;
}
