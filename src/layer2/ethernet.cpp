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

MacAddr::MacAddr (void) {
    memset (addr, 0, MacAddrLen);
}

MacAddr::MacAddr (uint8_t const * pkt) {
    memcpy (addr, pkt, MacAddrLen);
}

uint8_t const * MacAddr::getAddr (void) const {
    return addr;
}

ostream & operator<< (ostream &output, MacAddr const &addr) {
    for (int i=0; i<MacAddrLen; i++) {
        output << (i!=0 ? ":" : "");
        output << hex << setfill('0') << setw (2) << +addr.addr[i];
    }
    return output;
}
