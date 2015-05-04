/*
====================
File: LoadPlaylistDlg.cc
Author: Shane Lillie
Description: CLoadPlaylistDlg module source.

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

#include "EnFunctions.h"

#include "LoadPlaylistDlg.h"


/*
 *  CLoadPlaylistDlg methods
 *
 */


CLoadPlaylistDlg::CLoadPlaylistDlg()
    : CDialogImpl<CLoadPlaylistDlg>(), CWinDataExchange<CLoadPlaylistDlg>()
{
}


LRESULT CLoadPlaylistDlg::OnInitDialogMsg(HWND /*hWndFocus*/, LPARAM /*lParam*/)
{
    CWaitCursor wc;

	CenterWindow(GetParent());
	return TRUE;
}


LRESULT CLoadPlaylistDlg::OnCloseMsg()
{
	EndDialog(IDCANCEL);
    return 0;
}


LRESULT CLoadPlaylistDlg::OnOkCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/)
{
    // get the values
    DoDataExchange(TRUE);

	EndDialog(wID);
    return 0;
}


LRESULT CLoadPlaylistDlg::OnCancelCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/)
{
    EndDialog(wID);
    return 0;
}
