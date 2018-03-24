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
