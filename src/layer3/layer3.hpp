/*
 * layer3.hpp
 *
 * Created by Rohit Saluja on 4/5/2018.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#ifndef LAYER3_H_
#define LAYER3_H_

#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

/*
 * @brief
 * Class for Layer3 header
 */
class Layer3 {
    protected:
    uint8_t ver:4;
};

/*
 * @brief
 * Different layer3 proto values
 */
#define IP_PROTO_ICMP   1
#define IP_PROTO_IGMP   2
#define IP_PROTO_TCP    6
#define IP_PROTO_UDP    17

/*
 * @brief
 * Class for layer3-proto of packet
 */
class L3Proto {
    private:
    uint8_t proto;

    public:
    L3Proto (void);
    L3Proto (const uint8_t val);
    uint8_t const Proto (void) const;
    string const Name (void) const;
    friend ostream & operator<< (ostream &output, L3Proto const &proto);
    friend bool const operator== (L3Proto const &lhs, L3Proto const &rhs);
    friend bool const operator!= (L3Proto const &lhs, L3Proto const &rhs);
};

#endif // LAYER3_H_
