/*
 * layer3.cpp
 *
 * Created by Rohit Saluja on 4/5/2018.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include "layer3.hpp"

using namespace std;

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
 * operator== overloaded to tell if
 * protocol numbers are equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if proto values are equal
 */
bool const operator== (L3Proto const &lhs, L3Proto const &rhs) {
    return lhs.proto == rhs.proto;
}

/*
 * @brief
 * operator!= overloaded to tell if
 * protocol numbers are not equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if proto values are not equal
 */
bool const operator!= (L3Proto const &lhs, L3Proto const &rhs) {
    return lhs.proto != rhs.proto;
}

