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
