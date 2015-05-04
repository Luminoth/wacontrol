/*
====================
File: SysTrayIcon.h
Author: Shane Lillie
Description: CSysTrayIcon module header.

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

#if !defined __SYSTRAYICON_H__
#define __SYSTRAYICON_H__

#if _MSC_VER >= 1000
#pragma once
#endif

#include "ShellNotifyIcon.h"


/*
class CSysTrayIcon
*/
class CSysTrayIcon : public CShellNotifyIcon<CSysTrayIcon>
{
public:
    CSysTrayIcon();

public:
	BEGIN_MSG_MAP(CSysTrayIcon)
	END_MSG_MAP()

private:
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
};


#endif
