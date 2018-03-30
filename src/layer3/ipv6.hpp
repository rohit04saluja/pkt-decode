/*
 * ipv6.hpp
 *
 * Created by Rohit Saluja on 3/30/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#ifndef IPV6_H_
#define IPV6_H_

#include <iostream>
#include <cstdint>

using namespace std;

/* 
 * @brief
 * Lengths of different components of ipv6 header
 */
#define Ipv6AddrLen    16 

/*
 * @brief
 * Class for Ipv6 address of packet
 */
class Ipv6Addr {
    private:
    uint8_t addr[Ipv6AddrLen];

    public:
    Ipv6Addr (void);
    Ipv6Addr (uint8_t const *pkt);
    uint8_t const * Addr (void) const;
    friend ostream & operator<< (ostream &output, Ipv6Addr const &addr);
    friend bool const operator== (Ipv6Addr const &lhs, Ipv6Addr const &rhs);
    friend bool const operator!= (Ipv6Addr const &lhs, Ipv6Addr const &rhs);
};

#endif  // IPV6_H_
