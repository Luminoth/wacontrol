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


const std::string CONFIG_HEADER = "# wacontrol.cfg - WinAmp Network Controller configuration file\n"
                              "#\n"
                              "# Supported options:\n"
                              "#\n"
                              "#\tserver = The server to connect to (default localhost)\n"
                              "#\tport = The port to connect on (default " + APP_PORT_STR + ")\n"
                              "\n";


const ConfigOption CONFIG[] =
{
    ConfigOption("server", "localhost"),
    ConfigOption("port", APP_PORT_STR),
    ConfigOption()
};
