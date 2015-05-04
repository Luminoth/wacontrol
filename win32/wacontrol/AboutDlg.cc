/*
====================
File: AboutDlg.cpp
Author: Shane Lillie
Description: CAboutDlg module source.

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

#include "AboutDlg.h"


/*
 *  CAboutDlg methods
 *
 */


LRESULT CAboutDlg::OnInitDialogMsg(HWND /*hWndFocus*/, LPARAM /*lParam*/)
{
    CWaitCursor wc;

	CenterWindow(GetParent());
	return TRUE;
}


LRESULT CAboutDlg::OnCloseMsg()
{
	EndDialog(0);
    return 0;
}


LRESULT CAboutDlg::OnOkCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    return SendMessage(WM_CLOSE);
}
