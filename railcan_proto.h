/**
 * Copyright (C) 2012-2015 R.L. Feenstra <reinderfeenstra@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301
 * USA
 */

#ifndef _RAILCAN_PROTO_H_
#define _RAILCAN_PROTO_H_

#include <stdint.h>

#define RAILCAN_VERSION_MAJOR  0
#define RAILCAN_VERSION_MINOR  0
#define RAILCAN_VERSION_PATCH  0

#define RAILCAN_SID_MESSAGE_BITS      4
#define RAILCAN_SID_MESSAGE_MASK      0x780
#define RAILCAN_SID_MESSAGE_RESET     0x0
#define RAILCAN_SID_MESSAGE_DCC       0x1
#define RAILCAN_SID_MESSAGE_INPUTS    0x2
#define RAILCAN_SID_MESSAGE_OUTPUTS   0x3
#define RAILCAN_SID_MESSAGE_STATUS    0xe
#define RAILCAN_SID_MESSAGE_INFO      0xf

#define RAILCAN_SID_ADDRESS_BITS      7
#define RAILCAN_SID_ADDRESS_MASK      0x07f
#define RAILCAN_SID_ADDRESS_BROADCAST 0x000 //!< 0
#define RAILCAN_SID_ADDRESS_FIRST     0x001 //!< 1
#define RAILCAN_SID_ADDRESS_LAST      0x07e //!< 126
#define RAILCAN_SID_ADDRESS_RESERVED  0x07f //!< 127

#define RAILCAN_SID_MASK ( RAILCAN_SID_MESSAGE_MASK | RAILCAN_SID_ADDRESS_MASK )

#define RAILCAN_SID( msg , addr )  ( ( ( msg ) << RAILCAN_SID_ADDRESS_BITS ) | ( addr ) )
#define RAILCAN_SID_TO_MESSAGE( id ) ( ( ( id ) & RAILCAN_SID_MESSAGE_MASK ) >> RAILCAN_SID_ADDRESS_BITS )
#define RAILCAN_SID_TO_ADDRESS( id ) ( ( id ) & RAILCAN_SID_ADDRESS_MASK )

#define RAILCAN_SID_RESET  RAILCAN_SID( RAILCAN_SID_MESSAGE_RESET , RAILCAN_SID_ADDRESS_BROADCAST )


#define RAILCAN_STATUSTYPE_UNKNOWN   0x00
#define RAILCAN_STATUSTYPE_BOOSTER   0x01
#define RAILCAN_STATUSTYPE_RESERVED  0xff

#define RAILCAN_NODETYPE_UNKNOWN  0x00
#define RAILCAN_NODETYPE_IO       0x01
#define RAILCAN_NODETYPE_DCC      0x02

typedef struct
{
  struct
  {
    uint8_t reserved : 5; //!< must be zero
    uint8_t id       : 3; //!<
  };
  uint16_t voltage; //!< in mV
  uint16_t current; //!< in mA
}  __attribute__((__packed__)) railcan_message_status_booster_t;

typedef struct
{
  uint8_t status_type;
  union
  {
    railcan_message_status_booster_t booster;
  };
}  __attribute__((__packed__)) railcan_message_status_t;

typedef struct
{
  uint8_t digital_input_count;  //!< 0..64
  uint8_t digital_output_count; //!< 0..64
} __attribute__((__packed__)) railcan_message_info_io_t;

typedef struct
{
  uint8_t booster_count; //!< 0..8
} __attribute__((__packed__)) railcan_message_info_dcc_t;

typedef struct
{
  uint8_t node_type;
  union
  {
    railcan_message_info_io_t  io;
    railcan_message_info_dcc_t dcc;
  };
} __attribute__((__packed__)) railcan_message_info_t;

#endif
