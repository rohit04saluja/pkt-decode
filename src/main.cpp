/*
 * main.cpp
 *
 * Created by Rohit Saluja on 3/22/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "decode.hpp"

using namespace std;

/*
 * @brief
 * API to get input from std in of packet hex dump
 *
 * @return
 * string with the hex dump pf the packet
 */
static string PktInput (void) {
    string in, pkt;
    cin >> in;
    while (in.find(".") == string::npos) {
        pkt += in;
        cin >> in;
    }
    pkt += (in.find(".")>0 ? in.substr(0, in.length()-1) : "");
    return pkt;
}

/*
 * @brief
 * API to replace all "0x" with "" to make a constant stream
 *
 * @param[in/out]
 * pkt      string with packet hex dump, modifications are done to this
 */
static void PktStrip_0x_ (string &pkt) {
    size_t pos;
    pos = pkt.find("0x");
    while (pos != string::npos) {
        pkt.replace(pos, 2, "");
        pos = pkt.find("0x");
    }
}

/*
 * @brief
 * API to convert Hex stream to number
 *
 * @param[in]
 * s        string with the hex number
 *
 * @return
 * uint8_t      the hex number in the string
 */
static uint8_t HexStrToNum (string s) {
    int x = 0;
    stringstream ss;
    ss << hex << s;
    ss >> x;
    return x;
}

/*
 * @brief
 * API to get packet from string of hex dump
 *
 * @param[in]
 * pktStr       Contains the hex dump of packet
 *
 * @param[in]
 * pkt          Pointer to buffer defined in the caller
 */
static void PktFromStr (string &pktStr, uint8_t * pkt) {
    int i = 0, len = pktStr.length()/2;
    for (string::iterator it=pktStr.begin(); i < len ; it++) {
        pkt[i++] = HexStrToNum(string(1, *it) + string(1, *++it));
    }
}

int main (int argc, char *argv[]) {
    string pktStr(PktInput());
    PktStrip_0x_(pktStr);
    size_t l = pktStr.length()/2;
    uint8_t pkt [l];
    PktFromStr(pktStr, pkt);
    decode(pkt, l);
    return 0;
}
