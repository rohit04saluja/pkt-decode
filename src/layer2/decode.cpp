/*
 * decode.cpp
 *
 * Created by Rohit Saluja on 3/22/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include "ethernet.hpp"

using namespace std;

int layer2_decode (uint8_t * pkt) {
    Ethernet eth(pkt);

    eth.print();
    pkt += EthernetLen;
    return EthernetLen;
}
