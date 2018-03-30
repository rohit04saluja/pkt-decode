/*
 * layer3_decode.cpp
 *
 * Created by Rohit Saluja on 3/30/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include "layer3_decode.hpp"
#include "ipv4.hpp"

using namespace std;

/*
 * @brief
 * API to decode layer3 of a packet
 *
 * @param[in]
 * pkt      pointer to the start of the packet
 *
 * @return
 * size of the layer3 header
 */
size_t layer3_decode (const uint8_t * pkt) {
    Ipv4 ip(pkt);
    if (ip.isValid()) {
        cout << "Layer3:" << endl;
        ip.print(2);
        return (ip.Ihl() * sizeof(uint32_t));
    }
    return 0;
}
