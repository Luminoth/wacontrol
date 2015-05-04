/*
====================
File: LoadPlaylistDlg.h
Author: Shane Lillie
Description: CLoadPlaylistDlg module header.

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

#if !defined __LOADPLAYLISTDLG_H__
#define __LOADPLAYLISTDLG_H__

#if _MSC_VER >= 1000
#pragma once
#endif


/*
class CLoadPlaylistDlg
*/
class CLoadPlaylistDlg : public CDialogImpl<CLoadPlaylistDlg>, public CWinDataExchange<CLoadPlaylistDlg>
{
public:
    CLoadPlaylistDlg();

public:
	enum { IDD = IDD_PLAYLIST_DIALOG };

	BEGIN_MSG_MAP(CLoadPlaylistDlg)
		MSG_WM_INITDIALOG(OnInitDialogMsg)
        MSG_WM_CLOSE(OnCloseMsg)
		COMMAND_ID_HANDLER_EX(IDOK, OnOkCmd)
        COMMAND_ID_HANDLER_EX(IDCANCEL, OnCancelCmd)
	END_MSG_MAP()

private:
    BEGIN_DDX_MAP(CLoadPlaylistDlg)
        DDX_TEXT(IDC_FILENAME_EDIT, m_filename)
    END_DDX_MAP()

public:
    const CString& playlist() const
    {
        return m_filename;
    }

private:
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialogMsg(HWND /*hWndFocus*/, LPARAM /*lParam*/);
    LRESULT OnCloseMsg();
	LRESULT OnOkCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/);
	LRESULT OnCancelCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/);

private:
    CString m_filename;
};


#endif
