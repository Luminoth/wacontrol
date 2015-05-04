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
#include "AboutDlg.h"


/*
 *  CMainDlg methods
 *
 */


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}


BOOL CMainDlg::OnIdle()
{
/* TODO: use DDX to handle this */
    char buffer[8];
    snprintf(buffer, 8, "%u", _Module.client_count());
    ::SetWindowText(GetDlgItem(IDC_CLIENTS_STATIC), buffer);

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


LRESULT CMainDlg::OnFileDetailsCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    ShowWindow(SW_SHOW);
    return 0;
}


LRESULT CMainDlg::OnAppAboutCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}


LRESULT CMainDlg::OnAppExitCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    m_trayicon.DeleteIcon(m_hWnd, 100);

	DestroyWindow();
	::PostQuitMessage(0);

    return 0;
}
