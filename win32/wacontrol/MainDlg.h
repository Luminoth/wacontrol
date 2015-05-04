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
        UPDATE_ELEMENT(ID_FILE_CONNECT, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_FILE_DISCONNECT, UPDUI_MENUPOPUP)

        UPDATE_ELEMENT(ID_WINAMP_EXECUTE, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_CLOSE, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_RESET, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_LOADPLAYLIST, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_PLAY, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_PLAYCD, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_PAUSE, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_STOP, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_PREVIOUSSONG, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_NEXTSONG, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_FFW5, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_REWIND5, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_VOLUMEUP, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_WINAMP_VOLUMEDOWN, UPDUI_MENUPOPUP)

        UPDATE_ELEMENT(ID_FILE_RESTORE, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MSG_WM_INITDIALOG(OnInitDialogMsg)
        MSG_WM_CLOSE(OnCloseMsg)
        MESSAGE_HANDLER_EX(WM_TRAYICON, OnTrayIconMsg)
        COMMAND_ID_HANDLER_EX(ID_FILE_CONNECT, OnFileConnectCmd)
        COMMAND_ID_HANDLER_EX(ID_FILE_DISCONNECT, OnFileDisconnectCmd)
        COMMAND_ID_HANDLER_EX(ID_FILE_RESTORE, OnFileRestoreCmd)
		COMMAND_ID_HANDLER_EX(ID_APP_EXIT, OnAppExitCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_EXECUTE, OnWinAmpExecCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_CLOSE, OnWinAmpCloseCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_RESET, OnWinAmpResetCmd)
        //COMMAND_ID_HANDLER_EX(ID_WINAMP_LOADPLAYLIST, OnWinAmpLoadPlaylist)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_PLAY, OnWinAmpPlayCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_PLAYCD, OnWinAmpPlayCDCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_PAUSE, OnWinAmpPauseCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_STOP, OnWinAmpStopCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_PREVIOUSSONG, OnWinAmpPrevCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_NEXTSONG, OnWinAmpNextCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_FFW5, OnWinAmpFFW5sCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_REWIND5, OnWinAmpRew5sCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_VOLUMEUP, OnWinAmpVolumeUpCmd)
        COMMAND_ID_HANDLER_EX(ID_WINAMP_VOLUMEDOWN, OnWinAmpVolumeDownCmd)
		COMMAND_ID_HANDLER_EX(ID_APP_ABOUT, OnAppAboutCmd)
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
    LRESULT OnFileConnectCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnFileDisconnectCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnFileRestoreCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
	LRESULT OnAppExitCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpExecCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpCloseCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpResetCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    //LRESULT OnWinAmpLoadPlaylist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpPlayCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpPlayCDCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpPauseCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpStopCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpPrevCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpNextCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpFFW5sCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpRew5sCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpVolumeUpCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
    LRESULT OnWinAmpVolumeDownCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);
	LRESULT OnAppAboutCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/);

private:
    HACCEL m_hAccelerator;
    CSysTrayIcon m_trayicon;
};


#endif
