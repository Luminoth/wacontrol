/*
====================
File: main.cc
Author: Shane Lillie
Description: Main application source.

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
 *  functions
 *
 */


bool previous_instance()
{
/* TODO: find a previous instance and
    show it if we do find it */

    return false;
}


int main(int argc, char* argv[])
{
    if(previous_instance())
        return 0;

    return g_application.run(argc, argv);
}
