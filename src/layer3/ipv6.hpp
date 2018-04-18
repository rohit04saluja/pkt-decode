/*
 * ipv6.hpp
 *
 * Created by Rohit Saluja on 3/30/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#ifndef IPV6_H_
#define IPV6_H_

#include "layer3.hpp"

using namespace std;

/* 
 * @brief
 * Lengths of different components of ipv6 header
 */
#define Ipv6AddrLen    16 
#define Ipv6Len        40

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

/*
 * @brief
 * Class for Ipv6 header
 */
class Ipv6 : public Layer3 {
    private:
    uint8_t tc;
    uint16_t fl:12;
    uint16_t len;
    uint8_t nh;
    uint8_t hl;
    Ipv6Addr srcip;
    Ipv6Addr dstip;

    public:
    Ipv6 (void);
    Ipv6 (const uint8_t * pkt);
    uint8_t TC (void) const;
    uint16_t FL (void) const;
    uint16_t Len (void) const;
    uint8_t NH (void) const;
    uint8_t HL (void) const;
    Ipv6Addr const SrcIp (void) const;
    Ipv6Addr const DstIp (void) const;
    bool const isValid (void)const;
    void print (const uint8_t ls=0) const;
    uint8_t const * HexDump (void) const;
    friend bool const operator== (Ipv6 const &lhs, Ipv6 const &rhs);
    friend bool const operator!= (Ipv6 const &lhs, Ipv6 const &rhs);
};

#endif  // IPV6_H_
