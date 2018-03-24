/*
 * ipv4.cpp
 *
 * Created by Rohit Saluja on 3/24/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <ipv4.hpp>
#include <iomanip>
#include <sstream>

using namespace std;

/*
 * Default constructor for class
 * initialize address to 0
 */
Ipv4Addr::Ipv4Addr (void) {
    memset(addr, 0, Ipv4AddrLen);
}

/*
 * Initialization constructor for class
 * initialize address from pointer to packet
 */
Ipv4Addr::Ipv4Addr (uint8_t const * pkt) {
    memcpy(addr, pkt, Ipv4AddrLen);
}

/*
 * @brief
 * Method to get the pointer to the address
 */
uint8_t const * Ipv4Addr::Addr (void) const {
    return addr;
}

/*
 * @brief
 * Method to print the address as string
 *
 * @param[in]
 * output       output where the string it to be printed
 * @param[in]
 * addr         ipv4 address obj
 *
 * @return
 * ostream object with ipv4 address in string
 */
ostream & operator<< (ostream &output, Ipv4Addr const &addr) {
    for (int i=0; i<Ipv4AddrLen; i++) {
        output << (i!=0 ? "." : "");
        output << +addr.addr[i];
    }
    return output;
}

/*
 * @brief
 * Method to check if two address are equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if memory of lhs is same as memory of rhs
 */
bool const operator== (Ipv4Addr const &lhs, Ipv4Addr const &rhs) {
    return (0==memcmp(lhs.addr, rhs.addr, Ipv4AddrLen));
}

/*
 * @brief
 * Method to check if two address are not equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if lhs==rhs is false
 */
bool const operator!= (Ipv4Addr const &lhs, Ipv4Addr const &rhs) {
    return !(lhs==rhs);
}


/*
 * @brief
 * Default constructor of class
 * initialize proto to 0
 */
L3Proto::L3Proto (void) {
    proto = 0;
}

/*
 * @brief
 * Initialization constructor of class
 * initializa proto form the val
 */
L3Proto::L3Proto (const uint8_t val) {
    proto = val;
}

/*
 * @brief
 * Method to get the proto value
 */
uint8_t const L3Proto::Proto (void) const {
    return proto;
}

/*
 * @brief
 * Method to get the name of proto value
 */
string const L3Proto::Name (void) const {
    switch(proto) {
        case IP_PROTO_ICMP:
            return "icmp";
        case IP_PROTO_IGMP:
            return "igmp";
        case IP_PROTO_TCP:
            return "tcp";
        case IP_PROTO_UDP:
            return "udp";
        default:
            return "unknown";
    }
}

/*
 * @brief
 * operator<< overloaded to print value
 *
 * @param[in]
 * output       ostream object
 * @parma[in]
 * proto        value of proto
 *
 * @return
 * ostream with string value of proto
 */
ostream & operator<< (ostream &output, L3Proto const &proto) {
    output << +proto.proto;
    return output;
}


/*
 * @brief
 * Defulat constructor for class
 * initialize the flag to 0
 */
Ipv4Flag::Ipv4Flag (void) {
    flag = 0;
}

/*
 * @brief
 * Initialization construct for class
 * initialize the flag from val
 */
Ipv4Flag::Ipv4Flag (const uint8_t val) {
    flag = 0x7 & val;
}

/*
 * @brief
 * Method to get the value of flag
 */
uint8_t const Ipv4Flag::Flag (void) const {
    return flag;
}

/*
 * @brief
 * Method to get the name of flag
 */
string const Ipv4Flag::Name (void) const {
    switch(flag) {
        case IPV4_FLAG_RSVD:
            return "reserved";
        case IPV4_FLAG_DF:
            return "df";
        case IPV4_FLAG_MF:
            return "mf";
        default:
            return "unknown";
    }
}

/*
 * @brief
 * operator<< overloaded to print value
 *
 * @param[in]
 * output       ostream object
 * @param[in]
 * flag         value to be printed
 *
 * @return
 * output with value of flag in string
 */
ostream & operator<< (ostream &output, Ipv4Flag const &flag) {
    output << flag.flag;
    return output;
}

/*
 * @brief
 * operator== overloaded to tell
 * if flags are equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if flags are equal
 */
bool const operator== (Ipv4Flag const &lhs, Ipv4Flag const &rhs) {
    return lhs.flag == rhs.flag;
}

/*
 * @brief
 * operator!= overloaded to tell
 * if flags are not equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if flags are not equal
 */
bool const operator!= (Ipv4Flag const &lhs, Ipv4Flag const &rhs) {
    return lhs.flag != rhs.flag;
}
