/*
 * ipv6.cpp
 *
 * Created by Rohit Saluja on 3/30/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <iomanip>
#include <sstream>
#include "ipv6.hpp"
#include <regex>

using namespace std;

/*
 * @brief
 * Default constructor for class
 * initialize values to 0
 */
Ipv6Addr::Ipv6Addr (void) {
    memset(addr, 0, Ipv6AddrLen);
}

/*
 * @brief
 * Initialization constructor for class
 * initialize the address from packet
 */
Ipv6Addr::Ipv6Addr (uint8_t const *pkt) {
    memcpy(addr, pkt, Ipv6AddrLen);
}

/*
 * @brief
 * Method to get pointer to address
 *
 * @return
 * pointer to address
 */
uint8_t const * Ipv6Addr::Addr (void) const {
    return addr;
}

/*
 * @brief
 * Method to print the address in string format
 *
 * @param[in]
 * output   ostream object for print
 * @param[in]
 * addr     object of ipv6 address
 *
 * @return
 * ostream object with output
 */
ostream & operator<< (ostream &output, Ipv6Addr const &addr) {
    stringstream s;
    for (uint8_t i=0; i<Ipv6AddrLen; i+=2) {
        s << (i==0 ? "" : ":");
        s << hex << ntohs(*((uint16_t *) (addr.addr + i)));
    }
    string str = s.str();
    regex pttrn(":(0:0(:0)*)");
    str = regex_replace (str, pttrn, ":");
    output << str;
    return output;
}

/*
 * @brief
 * Method to compare if addresses are equal
 *
 * @parma[in]
 * lhs      left side of operator
 * @parma[in]
 * rhs      right side of operator
 *
 * @return
 * true if addresses are equal
 */
bool const operator== (Ipv6Addr const &lhs, Ipv6Addr const &rhs) {
    return (0==memcmp(lhs.addr, rhs.addr, Ipv6AddrLen));
}

/*
 * @brief
 * Method to compare if addresses are not equal
 *
 * @parma[in]
 * lhs      left side of operator
 * @parma[in]
 * rhs      right side of operator
 *
 * @return
 * true if operator== is false
 */
bool const operator!= (Ipv6Addr const &lhs, Ipv6Addr const &rhs) {
    return !(lhs==rhs);
}


/*
 * @brief
 * Default constructor for class
 * initialize values to 0
 */
Ipv6::Ipv6 (void) : Layer3::Layer3() {
    tc = 0;
    fl = 0;
    len = 0;
    nh = 0;
    hl = 0;
    srcip = Ipv6Addr();
    dstip = Ipv6Addr();
}
