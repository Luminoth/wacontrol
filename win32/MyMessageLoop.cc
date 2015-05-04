/*
====================
File: MyMessageLoop.cc
Author: Shane Lillie
Description: CMyMessageLoop module source.

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

#include "MyMessageLoop.h"


/*
 *  CMyMessageLoop methods
 *
 */


int CMyMessageLoop::Run()
{
    while(true) {
        // check for messages
        if(PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE)) {
            // quit on WM_QUIT
            if(WM_QUIT == m_msg.message) {
				ATLTRACE2(atlTraceUI, 0, _T("CMyMessageLoop::Run - exiting\n"));
				break;
            }

            // translate and dispatch
            if(!PreTranslateMessage(&m_msg)) {
                ::TranslateMessage(&m_msg);
                ::DispatchMessage(&m_msg);
            }
        } else {
            // idle if no
            // other messages
            OnIdle(0);
        }
    }
    return (int)m_msg.message;
}
