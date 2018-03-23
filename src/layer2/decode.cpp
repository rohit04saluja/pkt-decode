/*
 * decode.cpp
 *
 * Created by Rohit Saluja on 3/22/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include "decode.hpp"
#include "ethernet.hpp"

using namespace std;

/*
 * @brief
 * API to decode layer2 of a packet
 *
 * @param[in]
 * pkt      pointer to the start of the packet
 *
 * @return
 * size of the layer2 header
 */
size_t layer2_decode (const uint8_t * pkt) {
    EthVlanTagSingle eth(pkt);
    
    if (eth.isValid()) {
        eth.print();
        return EthVlanTagSingleLen;
    } else {
        Ethernet(pkt).print();
        return EthernetLen;
    }
}
