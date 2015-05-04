/*
====================
File: config.cc
Author: Shane Lillie
Description: Configuration constructs source.

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

#include "pch.h"


/*
 *  constants
 *
 */


const std::string CONFIG_HEADER = _T("# ") + DEFAULT_CONFIG + _T(" - WinAmp Network Controller configuration file\r\n"
                              "#\r\n"
                              "# Supported options:\r\n"
                              "#\r\n"
                              "#\tserver = The server to connect to (default localhost)\r\n"
                              "#\tport = The port to connect on (default ") + APP_PORT_STR + _T(")\r\n"
                              "\r\n");


const EnConfigOption CONFIG_OPTIONS[] =
{
    EnConfigOption("server", "localhost"),
    EnConfigOption("port", APP_PORT_STR),
    EnConfigOption()
};
