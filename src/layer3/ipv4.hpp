/*
 * ipv4.hpp
 *
 * Created by Rohit Saluja on 3/24/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#ifndef IPV4_H_
#define IPV4_H_

#include <iostream>
#include <cstdint>

using namespace std;

/*
 * @brief
 * Length os different components of ipv4 header
 */
#define Ipv4AddrLen     4

/*
 * @brief
 * Class for Ipv4 addrerss of packet
 */
class Ipv4Addr {
    private:
    uint8_t addr[Ipv4AddrLen];

    public:
    Ipv4Addr (void);
    Ipv4Addr (uint8_t const *pkt);
    uint8_t const * Addr (void) const;
    friend ostream & operator<< (ostream &output, Ipv4Addr const &addr);
    friend bool const operator== (Ipv4Addr const &lhs, Ipv4Addr const &rhs);
    friend bool const operator!= (Ipv4Addr const &lhs, Ipv4Addr const &rhs);
};
