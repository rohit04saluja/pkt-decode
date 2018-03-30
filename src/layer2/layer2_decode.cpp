/*
 * layer2_decode.cpp
 *
 * Created by Rohit Saluja on 3/22/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include "layer2_decode.hpp"
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
    if (EthVlanTagDouble(pkt).isValid()) {
        cout << "Layer2:" << endl;
        EthVlanTagDouble(pkt).print(2);
        return EthVlanTagDoubleLen;
    } else if (EthVlanTagSingle(pkt).isValid()) {
        cout << "Layer2:" << endl;
        EthVlanTagSingle(pkt).print(2);
        return EthVlanTagSingleLen;
    } else {
        cout << "Layer2:" << endl;
        Ethernet(pkt).print(2);
        return EthernetLen;
    }
}
