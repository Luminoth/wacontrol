/*
====================
File: pch.h
Author: Shane Lillie
Description: Precompiled header.

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

#if !defined __PCH_H__
#define __PCH_H__

#if _MSC_VER >= 1000
#pragma once
#endif

// Change these values to use different versions
#define _WIN32_WINDOWS  0x0410  // 9x >= 98
#define WINVER		    0x0410  // 9x >= 98
#define _WIN32_WINNT	0x0500  // NT >= 2000
#define _WIN32_IE	    0x0501  // IE >= 5.0.1
#define _RICHEDIT_VER	0x0200  // Richedit >= 2.0

#define _WTL_USE_CSTRING
#define _ATL_USE_DDX_FLOAT
#undef _ATL_MIN_CRT

#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include <cassert>

#include <atlbase.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlmisc.h>    // lots of good stuff
#include <atlddx.h>     // ddx stuff
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>   // extra controls
#include <atldlgs.h>
#include <atlcrack.h>   // message crackers
#include <atlsplit.h>   // CSplitterWindow
#include <atlsync.h>    // synchronization classes

#include "EnUtilities.h"
#include "EnNetUtilities.h"
#include "EnConfig.h"

#include "main.h"
#include "resource.h"
#include "messages.h"
#include "config.h"
#include "common.h"
#include "WACDApplication.h"

// re-define to keep classviewer
// from puking its lunch
#undef BEGIN_MSG_MAP
#define BEGIN_MSG_MAP(x) BEGIN_MSG_MAP_EX(x)


#endif