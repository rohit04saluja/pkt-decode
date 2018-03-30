/*
 * ipv4.cpp
 *
 * Created by Rohit Saluja on 3/24/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <iomanip>
#include <sstream>
#include <ipv4.hpp>

using namespace std;

/*
 * Default constructor for class
 * initialize address to 0
 */
Ipv4Addr::Ipv4Addr (void) {
    memset(addr, 0, Ipv4AddrLen);
}

/*
 * Initialization constructor for class
 * initialize address from pointer to packet
 */
Ipv4Addr::Ipv4Addr (uint8_t const * pkt) {
    memcpy(addr, pkt, Ipv4AddrLen);
}

/*
 * @brief
 * Method to get the pointer to the address
 */
uint8_t const * Ipv4Addr::Addr (void) const {
    return addr;
}

/*
 * @brief
 * Method to print the address as string
 *
 * @param[in]
 * output       output where the string it to be printed
 * @param[in]
 * addr         ipv4 address obj
 *
 * @return
 * ostream object with ipv4 address in string
 */
ostream & operator<< (ostream &output, Ipv4Addr const &addr) {
    output << dec;
    for (int i=0; i<Ipv4AddrLen; i++) {
        output << (i!=0 ? "." : "");
        output << +addr.addr[i];
    }
    return output;
}

/*
 * @brief
 * Method to check if two address are equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if memory of lhs is same as memory of rhs
 */
bool const operator== (Ipv4Addr const &lhs, Ipv4Addr const &rhs) {
    return (0==memcmp(lhs.addr, rhs.addr, Ipv4AddrLen));
}

/*
 * @brief
 * Method to check if two address are not equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if lhs==rhs is false
 */
bool const operator!= (Ipv4Addr const &lhs, Ipv4Addr const &rhs) {
    return !(lhs==rhs);
}


/*
 * @brief
 * Default constructor of class
 * initialize proto to 0
 */
L3Proto::L3Proto (void) {
    proto = 0;
}

/*
 * @brief
 * Initialization constructor of class
 * initializa proto form the val
 */
L3Proto::L3Proto (const uint8_t val) {
    proto = val;
}

/*
 * @brief
 * Method to get the proto value
 */
uint8_t const L3Proto::Proto (void) const {
    return proto;
}

/*
 * @brief
 * Method to get the name of proto value
 */
string const L3Proto::Name (void) const {
    switch(proto) {
        case IP_PROTO_ICMP:
            return "icmp";
        case IP_PROTO_IGMP:
            return "igmp";
        case IP_PROTO_TCP:
            return "tcp";
        case IP_PROTO_UDP:
            return "udp";
        default:
            return "unknown";
    }
}

/*
 * @brief
 * operator<< overloaded to print value
 *
 * @param[in]
 * output       ostream object
 * @parma[in]
 * proto        value of proto
 *
 * @return
 * ostream with string value of proto
 */
ostream & operator<< (ostream &output, L3Proto const &proto) {
    output << +proto.proto;
    return output;
}

/*
 * @brief
 * operator== overloaded to tell if
 * protocol numbers are equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if proto values are equal
 */
bool const operator== (L3Proto const &lhs, L3Proto const &rhs) {
    return lhs.proto == rhs.proto;
}

/*
 * @brief
 * operator!= overloaded to tell if
 * protocol numbers are not equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if proto values are not equal
 */
bool const operator!= (L3Proto const &lhs, L3Proto const &rhs) {
    return lhs.proto != rhs.proto;
}


/*
 * @brief
 * Defulat constructor for class
 * initialize the flag to 0
 */
Ipv4Flag::Ipv4Flag (void) {
    flag = 0;
}

/*
 * @brief
 * Initialization construct for class
 * initialize the flag from val
 */
Ipv4Flag::Ipv4Flag (const uint8_t val) {
    flag = 0x7 & val;
}

/*
 * @brief
 * Method to get the value of flag
 */
uint8_t const Ipv4Flag::Flag (void) const {
    return flag;
}

/*
 * @brief
 * Method to get the name of flag
 */
string const Ipv4Flag::Name (void) const {
    switch(flag) {
        case IPV4_FLAG_RSVD:
            return "reserved";
        case IPV4_FLAG_DF:
            return "df";
        case IPV4_FLAG_MF:
            return "mf";
        default:
            return "unknown";
    }
}

/*
 * @brief
 * operator<< overloaded to print value
 *
 * @param[in]
 * output       ostream object
 * @param[in]
 * flag         value to be printed
 *
 * @return
 * output with value of flag in string
 */
ostream & operator<< (ostream &output, Ipv4Flag const &flag) {
    output << +flag.flag;
    return output;
}

/*
 * @brief
 * operator== overloaded to tell
 * if flags are equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if flags are equal
 */
bool const operator== (Ipv4Flag const &lhs, Ipv4Flag const &rhs) {
    return lhs.flag == rhs.flag;
}

/*
 * @brief
 * operator!= overloaded to tell
 * if flags are not equal
 *
 * @param[in]
 * lhs      left side of operator
 * @param[in]
 * rhs      right side of operator
 *
 * @return
 * true if flags are not equal
 */
bool const operator!= (Ipv4Flag const &lhs, Ipv4Flag const &rhs) {
    return lhs.flag != rhs.flag;
}


/*
 * @brief
 * Default constructor for class
 * initialize all values to and correct len
 */
Ipv4::Ipv4 (void) {
    ver = 0xf & Ipv4Version;
    ihl = 0xf & (Ipv4MinLen / sizeof(uint32_t));
    dscp = 0;
    ecn = 0;
    len = 0;
    id = 0;
    flag = 0;
    off = 0;
    ttl = 0;
    proto = L3Proto();
    srcip = Ipv4Addr();
    dstip = Ipv4Addr();
    this->GenChksum();
}

/*
 * @brief
 * Initialization constructor for class
 * initialize header from packet
 */
Ipv4::Ipv4 (const uint8_t * pkt) {
    ver = 0xf & (pkt[0] >> 4);
    ihl = 0xf & pkt[0];
    dscp = 0x3f & (pkt[1] >> 2);
    ecn = 0x3 & pkt[1];
    len = ntohs(*((uint16_t *) (pkt+2)));
    id = ntohs(*((uint16_t *) (pkt+4)));
    flag = 0x7 & (pkt[6] >> 5);
    off = 0x1fff & ntohs(*((uint16_t *) (pkt + 6)));
    ttl = pkt[8];
    proto = L3Proto (pkt[9]);
    chksum = ntohs(*((uint16_t *) (pkt+10)));
    srcip = Ipv4Addr(pkt + 12);
    dstip = Ipv4Addr(pkt + 12 + Ipv4AddrLen);
}

/*
 * @brief
 * Method to get IHL
 *
 * @return
 * value of IHL
 */
uint8_t const Ipv4::Ihl (void) const {
    return ihl;
}

/*
 * @brief
 * Method to get DSCP
 *
 * @return
 * value of DSCP
 */
uint8_t const Ipv4::Dscp (void) const {
    return dscp;
}

/*
 * @brief
 * Method to get ECN
 *
 * @return
 * value of ECN
 */
uint8_t const Ipv4::Ecn (void) const {
    return ecn;
}

/*
 * @brief
 * Method to get length of packet
 *
 * @return
 * value of the length of packet
 */
uint16_t const Ipv4::Len (void) const {
    return len;
}

/*
 * @brief
 * Method to get ID
 *
 * @return
 * value of ID
 */
uint16_t const Ipv4::Id (void) const {
    return id;
}

/*
 * @brief
 * Method to get flag
 *
 * @return
 * value of flag
 */
Ipv4Flag const Ipv4::Flag (void) const {
    return flag;
}

/*
 * @brief
 * Method to get fragment offset
 *
 * @return
 * value of fragment offset
 */
uint16_t const Ipv4::Off (void) const {
    return off;
}

/*
 * @brief
 * Method to get TTL
 */
uint8_t const Ipv4::Ttl (void) const {
    return ttl;
}

/*
 * @brief
 * Method to get protocol
 *
 * @return
 * object of protocol number
 */
L3Proto const Ipv4::Proto (void) const {
    return proto;
}

/*
 * @brief
 * Method to get checksum
 *
 * @return
 * value of checksum
 */
uint16_t const Ipv4::Chksum (void) const {
    return chksum;
}

/*
 * @brief
 * Method to get source IP
 *
 * @return
 * object of source IP
 */
Ipv4Addr const Ipv4::SrcIp (void) const {
    return srcip;
}

/*
 * @brief
 * Method to get destination IP
 *
 * @return
 * object of destination IP
 */
Ipv4Addr const Ipv4::DstIp (void) const {
    return dstip;
}

/*
 * @brief
 * Method to get the sum of all
 * field in header except chksum
 *
 * @return
 * sum of all fields
 */
uint32_t const Ipv4::FieldSum (void) const {
    const uint8_t *addr;
    uint32_t sum = 0;
    sum += ver << 12;
    sum += ihl << 8;
    sum += dscp << 2;
    sum += ecn;
    sum += len;
    sum += id;
    sum += flag.Flag() << 13;
    sum += off;
    sum += ttl << 8;
    sum += proto.Proto();
    addr = srcip.Addr();
    for (uint8_t i=0; i<Ipv4AddrLen; i++) {
        if (i%2 == 0) {
            sum += addr[i] << 8;
        } else {
            sum += addr[i];
        }
    }
    addr = dstip.Addr();
    for (uint8_t i=0; i<Ipv4AddrLen; i++) {
        if (i%2 == 0) {
            sum += addr[i] << 8;
        } else {
            sum += addr[i];
        }
    }
    return sum;
}

/*
 * @brief
 * Method to add carry to sum
 *
 * @param[in]
 * sum      orginal sum
 *
 * @return
 * updated sum in 16 bit
 */
uint16_t const Ipv4::SumToUint16 (uint32_t sum) const {
    for (uint16_t carry=sum>>16; carry!=0; carry=sum>>16) {
        sum = sum & 0xffff;
        sum += carry;
    }
    return sum & 0xffff;
}

/*
 * @brief
 * Method to generate checksum from packet
 */
void Ipv4::GenChksum (void) {
    uint32_t sum = this->FieldSum();
    sum = this->SumToUint16(sum);
    chksum = ~sum;
}
 

/*
 * @brief
 * Method to verify if checksum is correct
 *
 * @return
 * true if checksum value if correct
 */
bool const Ipv4::VerifyChksum (void) const {
    uint32_t sum = this->FieldSum() + chksum;
    sum = this->SumToUint16(sum);
    if (sum == 0xffff) {
        return true;
    }
    return false;
}

/*
 * @brief
 * Method to validate the if this is ipv4 header
 *
 * @return
 * true if packet header is valid
 */
bool const Ipv4::isValid (void) const {
    if (ver == 4) {
        return true;
    }
    return false;
}

/*
 * @brief
 * Method to print the ipv4 header
 *
 * @param[in]
 * ls       number of leading spaces
 */
void Ipv4::print (const uint8_t ls) const {
    cout << string(ls, ' ') << "Version: " << +ver << endl;
    cout << string(ls, ' ') << "Header Len: " << +ihl << " (" << dec << ihl * sizeof(uint32_t) << "B)" << endl;
    cout << string(ls, ' ') << "DSCP: " << +dscp << endl;
    cout << string(ls, ' ') << "ECN: " << +ecn << endl;
    cout << string(ls, ' ') << "Total Len: " << dec << len << endl;
    cout << string(ls, ' ') << "Id: " << id << endl;
    cout << string(ls, ' ') << "Flag: " << flag << " (" << flag.Name() << ")" << endl;
    cout << string(ls, ' ') << "Frag Offset: " << off << endl;
    cout << string(ls, ' ') << "TTL: " << +ttl << endl;
    cout << string(ls, ' ') << "Protocol: " << proto << " (" << proto.Name() << ")" << endl;
    cout << string(ls, ' ') << "Checksum: 0x" << setfill('0') << setw(4) << hex << chksum << endl;
    cout << string(ls, ' ') << "Source Ip: " << srcip << endl;
    cout << string(ls, ' ') << "Destination Ip: " << dstip << endl;
}

/*
 * @brief
 * Method to print the hexdump of
 * ipv4 header from obj
 *
 * @return
 * point to the memory with hex dump
 */
uint8_t const * Ipv4::HexDump (void) const {
    uint8_t * head = (uint8_t *) malloc(ihl);
    head[0] = (ver << 4) + ihl;
    head[1] = (dscp << 2) + ecn;
    head[2] = len >> 8;
    head[3] = len;
    head[4] = id >> 8;
    head[5] = id;
    head[6] = (flag.Flag() << 5) + (off >> 8);
    head[7] = off;
    head[8] = ttl;
    head[9] = proto.Proto();
    head[10] = chksum >> 8;
    head[11] = chksum;
    memcpy(head+12, srcip.Addr(), Ipv4AddrLen);
    memcpy(head+12+Ipv4AddrLen, dstip.Addr(), Ipv4AddrLen);
    return head;
}

/*
 * @brief
 * operator== overloaded to tell if
 * ipv4 headers are equal
 *
 * @param[in]
 * lhs      left side of argument
 * @param[in]
 * rhs      right side of argument
 *
 * @return
 * true if all fields are equal
 */
bool const operator== (Ipv4 const &lhs, Ipv4 const &rhs) {
    if (lhs.ver == rhs.ver &&
        lhs.ihl == rhs.ihl &&
        lhs.dscp == rhs.dscp &&
        lhs.ecn == rhs.ecn &&
        lhs.len == rhs.len &&
        lhs.id == rhs.id &&
        lhs.flag == rhs.flag &&
        lhs.off == rhs.off &&
        lhs.ttl == rhs.ttl &&
        lhs.proto == rhs.proto &&
        lhs.chksum == rhs.chksum &&
        lhs.srcip == rhs.srcip &&
        lhs.dstip == rhs.dstip) {
        return true;
    }
    return false;
}

/*
 * @brief
 * operator!= overloaded to tell if
 * ipv4 headers are not equal
 *
 * @param[in]
 * lhs      left side of argument
 * @param[in]
 * rhs      right side of argument
 *
 * @return
 * true if lhs==rhs is false
 */
bool const operator!= (Ipv4 const &lhs, Ipv4 const &rhs) {
    return !(lhs==rhs);
}
