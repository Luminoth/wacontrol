/*
====================
File: MyMessageLoop.h
Author: Shane Lillie
Description: CMyMessageLoop module header.

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

#if !defined __MYMESSAGELOOP_H__
#define __MYMESSAGELOOP_H__

#if _MSC_VER >= 1000
#pragma once
#endif


/*
class CMyMessageLoop

NOTE: Idea taken from http://www.codeproject.com/wtl/wtlgameloop.asp

NOTE: CMessageLoop::Run is not a virtual function.
Therefore if CMyMessageLoop::Run is to be used polymorphically,
then you will need to modify the WTL header file atlapp.h,
in order to make CMessageLoop::Run a virtual function.
This will allow CMyMessageLoop::Run to function properly
when used in a polymorphic setting. Fortunately for most regular uses,
this will not need to be done.
*/
class CMyMessageLoop : public CMessageLoop
{
public:
    virtual int Run();
};


#endif
