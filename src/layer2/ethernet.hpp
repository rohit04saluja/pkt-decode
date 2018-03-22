/*
 * ethernet.hpp
 *
 * Created by Rohit Saluja on 3/22/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_

#include <iostream>
#include <cstdint>

using namespace std;

#define MacAddrLen      6

/*
 * @brief
 * Class for mac address of packet
 */
class MacAddr {
    private:
    uint8_t addr[MacAddrLen];

    public:
    MacAddr (void);
    MacAddr (uint8_t const * pkt);
    uint8_t const * getAddr (void) const;
    friend ostream & operator<< (ostream &output, MacAddr const &addr);
};

#endif  // ETHERNET_H_
