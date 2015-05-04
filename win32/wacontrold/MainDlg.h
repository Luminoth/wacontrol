/*
====================
File: MainDlg.h
Author: Shane Lillie
Description: CMainDlg module header.

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

#if !defined __MAINDLG_H__
#define __MAINDLG_H__

#if _MSC_VER >= 1000
#pragma once
#endif

#include "SysTrayIcon.h"


/*
class CMainDlg
*/
class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MSG_WM_INITDIALOG(OnInitDialogMsg)
        MSG_WM_CLOSE(OnCloseMsg)
        MESSAGE_HANDLER_EX(WM_TRAYICON, OnTrayIconMsg)
        COMMAND_ID_HANDLER_EX(ID_FILE_DETAILS, OnFileDetailsCmd)
		COMMAND_ID_HANDLER_EX(ID_APP_ABOUT, OnAppAboutCmd)
		COMMAND_ID_HANDLER_EX(ID_APP_EXIT, OnAppExitCmd)
        CHAIN_MSG_MAP(CUpdateUI<CMainDlg>)
        REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

private:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

private:
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialogMsg(HWND /*hWndFocus*/, LPARAM /*lParam*/);
    LRESULT OnCloseMsg();
    LRESULT OnTrayIconMsg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam);
	LRESULT OnFileDetailsCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
	LRESULT OnAppAboutCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
	LRESULT OnAppExitCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);

private:
    CSysTrayIcon m_trayicon;
};


#endif
