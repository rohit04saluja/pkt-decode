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

/*
 * @brief
 * Default constructor for class
 * inititalize the address to 0
 */
MacAddr::MacAddr (void) {
    memset (addr, 0, MacAddrLen);
}

/*
 * @brief
 * Constructor to initialize the
 * address from given bye stream
 *
 * @param[in]
 * pkt     top of the address stream
 */
MacAddr::MacAddr (uint8_t const * pkt) {
    memcpy (addr, pkt, MacAddrLen);
}

/*
 * @brief
 * Method to get a pointer to start of address
 *
 * @return
 * pointer to start of address
 */
uint8_t const * MacAddr::getAddr (void) const {
    return addr;
}

/*
 * @brief
 * operator<< overloaded for printing the address
 *
 * @param[in]
 * output   output stream
 * @paramp[in]
 * addr     mac address class
 *
 * @return
 * output stream with the prints
 */
ostream & operator<< (ostream &output, MacAddr const &addr) {
    for (int i=0; i<MacAddrLen; i++) {
        output << (i!=0 ? ":" : "");
        output << hex << setfill('0') << setw(2) << +addr.addr[i];
    }
    return output;
}
