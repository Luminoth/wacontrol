/*
====================
File: common.h
Author: Shane Lillie
Description: Common constants and such.

(c) 2004 Energon Software

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
====================
*/

#if !defined __MAIN_H__
#define __MAIN_H__


#include <string>


/*
 *  constants
 *
 */


const unsigned short APP_PORT(1205);
const std::string APP_PORT_STR("1205");


/*
 *  packet headers
 *
 */


enum PacketType
{
    PacketNull,         // invalid packet
    PacketDisconnect,   // 2-byte packet
    PacketWinAmpExec,   // 2-byte packet
    PacketWinAmpClose,  // 2-byte packet
    PacketWinAmpReset,  // 2-byte packet
    PacketWinAmpPlay,   // 2-byte packet
    PacketWinAmpPause,  // 2-byte packet
    PacketWinAmpStop,   // 2-byte packet
    PacketWinAmpPrev,   // 2-byte packet
    PacketWinAmpNext,   // 2-byte packet
};


#endif
