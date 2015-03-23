//
//  IpHeaderDefinition.h
//  Li/Users/ludoviclaffineur/Documents/MoOS/utils/IpHeaderDefinitions.hbLoAndCap
//
//  Created by Ludovic Laffineur on 30/10/13.
//  Copyright (c) 2013 Ludovic Laffineur. All rights reserved.
//

#ifndef MoOS_IpHeaderDefinition_h
#define MoOS_IpHeaderDefinition_h
#include "pcap.h"

typedef struct ip_address_struct{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address_struct;

typedef union ip_address{
	ip_address_struct struct_bytes;
	u_int32_t int_address;
} ip_address;

typedef struct ip_header{
	u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
	u_char  tos;            // Type of service
	u_short tlen;           // Total length
	u_short identification; // Identification
	u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
	u_char  ttl;            // Time to live
	u_char  proto;          // Protocol
	u_short crc;            // Header checksum
	ip_address  saddr;      // Source address
	ip_address  daddr;      // Destination address
	u_int   op_pad;         // Option + Padding
}ip_header;

typedef struct udp_header{
	u_short sport;          // Source port
	u_short dport;          // Destination port
	u_short len;            // Datagram length
	u_short crc;            // Checksum
}udp_header;

typedef struct tcp_header{
	u_short sport;          // Source port
	u_short dport;          // Destination port
	u_short len;            // Datagram length
	u_short crc;            // Checksum
}tcp_header;




const long int TEN_ZERO_ZERO_ZERO  = 167772160;
const long int TEN_FIFTY_TWO  = 184549375;
const long int ONE_SEVENTY_TWO_MIN = 2886729728;
const long int ONE_SEVENTY_TWO_MAX = 2887778303;
const long int ONE_NINETY_TWO_MIN = 3232235520;
const long int ONE_NINETY_TWO_MAX = 3232301055;

const int NBR_IP_ADDRESSES = 1893989;

#endif