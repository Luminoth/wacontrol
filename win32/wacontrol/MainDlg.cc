/*
====================
File: MainDlg.cc
Author: Shane Lillie
Description: CMainDlg module source.

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

#include "MainDlg.h"
#include "ConnectDlg.h"
#include "LoadPlaylistDlg.h"
#include "AboutDlg.h"


/*
 *  CMainDlg methods
 *
 */


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
    if(::TranslateAccelerator(m_hWnd, m_hAccelerator, pMsg))
        return TRUE;
	return CWindow::IsDialogMessage(pMsg);
}


BOOL CMainDlg::OnIdle()
{
    bool connected = _Module.connected();

    UIEnable(ID_FILE_CONNECT, !connected);
    UIEnable(ID_FILE_DISCONNECT, connected);

    UIEnable(ID_WINAMP_EXECUTE, connected);
    UIEnable(ID_WINAMP_CLOSE, connected);
    UIEnable(ID_WINAMP_RESET, connected);
    UIEnable(ID_WINAMP_LOADPLAYLIST, FALSE);
    UIEnable(ID_WINAMP_PLAY, connected);
    UIEnable(ID_WINAMP_PLAYCD, FALSE);
    UIEnable(ID_WINAMP_PAUSE, connected);
    UIEnable(ID_WINAMP_STOP, connected);
    UIEnable(ID_WINAMP_PREVIOUSSONG, connected);
    UIEnable(ID_WINAMP_NEXTSONG, connected);
    UIEnable(ID_WINAMP_FFW5, connected);
    UIEnable(ID_WINAMP_REWIND5, connected);
    UIEnable(ID_WINAMP_VOLUMEUP, connected);
    UIEnable(ID_WINAMP_VOLUMEDOWN, connected);

    UIEnable(ID_FILE_RESTORE, !IsWindowVisible());

    UIUpdateChildWindows();

    _Module.handle_events();
	return FALSE;
}


LRESULT CMainDlg::OnInitDialogMsg(HWND /*hWndFocus*/, LPARAM /*lParam*/)
{
    CWaitCursor wc;

	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

    // load accelerator
    m_hAccelerator = AtlLoadAccelerators(IDR_MAINFRAME);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

    char buffer[64];
    AtlLoadString(IDR_MAINFRAME, buffer, 64);
    m_trayicon.AddIconMessage(m_hWnd, 100, LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME)), WM_TRAYICON, buffer);

	return TRUE;
}


LRESULT CMainDlg::OnCloseMsg()
{
    ShowWindow(SW_HIDE);
    return 0;
}


LRESULT CMainDlg::OnTrayIconMsg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam)
{
    if(lParam == WM_RBUTTONDOWN) {
        SetForegroundWindow(m_hWnd);

        POINT point;
        GetCursorPos(&point);

        HMENU hMenu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_TRAY_MENU));
        TrackPopupMenu(GetSubMenu(hMenu, 0), TPM_RIGHTBUTTON, point.x, point.y, 0, m_hWnd, NULL);

        DestroyMenu(hMenu);

        PostMessage(WM_NULL);
    } else if(lParam == WM_LBUTTONDBLCLK) {
/* TODO: send the restore command */
        ShowWindow(SW_SHOW);
        SetForegroundWindow(m_hWnd);
    }
    return 0;
}


LRESULT CMainDlg::OnFileConnectCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    CConnectDlg dlg;
	if(dlg.DoModal() == IDOK) {
        if(!_Module.connect())
            return 0;
    }
	return 0;
}


LRESULT CMainDlg::OnFileDisconnectCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    _Module.disconnect();
    return 0;
}


LRESULT CMainDlg::OnFileRestoreCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    ShowWindow(SW_SHOW);
    SetForegroundWindow(m_hWnd);
    return 0;
}


LRESULT CMainDlg::OnAppExitCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    m_trayicon.DeleteIcon(m_hWnd, 100);

	DestroyWindow();
	::PostQuitMessage(0);

    return 0;
}


LRESULT CMainDlg::OnWinAmpExecCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_exec())
        return 0;
	return 0;
}


LRESULT CMainDlg::OnWinAmpCloseCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_close())
        return 0;
    return 0;
}


LRESULT CMainDlg::OnWinAmpResetCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_reset())
        return 0;
    return 0;
}

#if 0
LRESULT CMainDlg::OnWinAmpLoadPlaylist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    CLoadPlaylistDlg dlg;
    if(dlg.DoModal() == IDOK) {
        if(!_Module.winamp_load(dlg.playlist()))
            return 0;
    }
    return 0;
}
#endif

LRESULT CMainDlg::OnWinAmpPlayCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_play())
        return 0;
    return 0;
}


LRESULT CMainDlg::OnWinAmpPlayCDCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
/* TODO: get which CD and everything */
    return 0;
}


LRESULT CMainDlg::OnWinAmpPauseCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_pause())
        return 0;
    return 0;
}


LRESULT CMainDlg::OnWinAmpStopCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_stop())
        return 0;
    return 0;
}


LRESULT CMainDlg::OnWinAmpPrevCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_prev())
        return 0;
    return 0;
}


LRESULT CMainDlg::OnWinAmpNextCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_next())
        return 0;
    return 0;
}


LRESULT CMainDlg::OnWinAmpFFW5sCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_ffw5s())
        return 0;
    return 0;
}


LRESULT CMainDlg::OnWinAmpRew5sCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_rew5s())
        return 0;
    return 0;
}


LRESULT CMainDlg::OnWinAmpVolumeUpCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_volume_up())
        return 0;
    return 0;
}


LRESULT CMainDlg::OnWinAmpVolumeDownCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    if(!_Module.winamp_volume_down())
        return 0;
    return 0;
}


LRESULT CMainDlg::OnAppAboutCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}
