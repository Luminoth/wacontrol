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

#if !defined __COMMON_H__
#define __COMMON_H__


#include <string>


/*
 *  constants
 *
 */


const unsigned short APP_PORT(1205);
const std::string APP_PORT_STR("1205");

const std::string DEFAULT_WINAMP_PATH("C:\\Program Files\\Winamp\\winamp.exe");


/*
 *  packet headers
 *
 */


enum PacketType
{
    PacketNull,             // invalid packet
    PacketDisconnect,       // 2-bytes
    PacketWinAmpExec,       // 2-bytes
    PacketWinAmpClose,      // 2-bytes
    PacketWinAmpReset,      // 2-bytes
    PacketWinAmpPlay,       // 2-bytes
    PacketWinAmpPlayCD,     // 4-bytes (header,cd#)
    PacketWinAmpPause,      // 2-bytes
    PacketWinAmpStop,       // 2-bytes
    PacketWinAmpPrev,       // 2-bytes
    PacketWinAmpNext,       // 2-bytes
    PacketWinAmpFFw5,       // 2-bytes
    PacketWinAmpRew5,       // 2-bytes
    PacketWinAmpVolumeSet,  // 4-bytes (header,volume)
    PacketWinAmpVolumeUp,   // 2-bytes
    PacketWinAmpVolumeDown, // 2-bytes
    PacketWinAmpPanningSet, // 4-bytes (header,panning)
    PacketWinAmpShuffleSet, // 4-bytes (header,bool)
    PacketWinAmpRepeatSet,  // 4-bytes (header,bool)
    //PacketWinAmpLoad,       // n-bytes (contains string address of playlist)
};


#endif
