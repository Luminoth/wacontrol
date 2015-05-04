/*
====================
File: config.h
Author: Shane Lillie
Description: Configuration constructs header.

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

#if !defined __CONFIG_H__
#define __CONFIG_H__

#if _MSC_VER >= 1000
#pragma once
#endif

#include <string>


struct ConfigOption;


/*
 *  constants
 *
 */


/*
NOTE: these should match up
to the CONFIG values
for easy indexing
*/
enum
{
    ConfigServer,
    ConfigPort,
    ConfigCount
};

// config header and options
extern const std::string CONFIG_HEADER;
extern const ConfigOption CONFIG[];


/*
struct ConfigOption
*/
struct ConfigOption
{
    std::string name;
    const std::string def_value;

    ConfigOption(const std::string& n=std::string(), const std::string& dv=std::string())
        : name(n), def_value(dv)
    {
    }
};


#endif
