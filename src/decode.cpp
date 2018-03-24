/*
 * decode.cpp
 *
 * Created by Rohit Saluja on 3/24/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <iomanip>
#include "decode.hpp"
#include "layer2_decode.hpp"

using namespace std;

/*
 * @brief
 * API to print packet as data
 *
 * @param[in]
 * pkt      pointer to start of packet
 *
 * @param[in]
 * s        size of packet to be used
 *
 * @param[in]
 * ls       leading spaces to be given (default=0)
 */
static void printData (const uint8_t * pkt, const size_t s, const uint8_t ls=0) {
    cout << string(ls, ' ') << "Data:";
    for (int i=0; i<s; i++) {
        cout << " " << "0x" << setfill('0') << setw(2) << +pkt[i];
    }
    cout << endl;
}

void decode (const uint8_t * pkt, const size_t l) {
    uint8_t pos = layer2_decode (pkt);
    printData (pkt+pos, l-pos);
}
