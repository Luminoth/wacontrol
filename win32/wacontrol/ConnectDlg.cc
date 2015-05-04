/*
====================
File: ConnectDlg.cc
Author: Shane Lillie
Description: CConnectDlg module source.

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

#include "ConnectDlg.h"


/*
 *  CConnectDlg methods
 *
 */


CConnectDlg::CConnectDlg()
    : CDialogImpl<CConnectDlg>(), CWinDataExchange<CConnectDlg>(),
        m_port(0)
{
}


void CConnectDlg::OnDataValidateError(UINT id, BOOL bSave, _XData& data)
{
    AtlMessageBox(m_hWnd, IDS_ERR_PORTRANGE, IDR_MAINFRAME, MB_OK | MB_ICONEXCLAMATION); 
    ::SetFocus(GetDlgItem(id));
}


LRESULT CConnectDlg::OnInitDialogMsg(HWND /*hWndFocus*/, LPARAM /*lParam*/)
{
    CWaitCursor wc;

    EnConfig& config(_Module.config());

    // save current changes
    // don't care about errors
    config.save();

    m_server = config.lookup(CONFIG_OPTIONS[ConfigServer].name).c_str();
    m_port = std::atoi(config.lookup(CONFIG_OPTIONS[ConfigPort].name).c_str());

    // set the values
    DoDataExchange();

	CenterWindow(GetParent());
	return TRUE;
}


LRESULT CConnectDlg::OnCloseMsg()
{
	EndDialog(IDCANCEL);
    return 0;
}


LRESULT CConnectDlg::OnOkCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/)
{
    // get the values
    DoDataExchange(TRUE);

    // handle invalid values
    if(m_server.IsEmpty())
        m_server = "localhost";
    if(!m_port) m_port = APP_PORT;

    // save the values
    EnConfig& config(_Module.config());
    config.set(CONFIG_OPTIONS[ConfigServer].name, static_cast<const char*>(m_server));

    char buffer[8];
    snprintf(buffer, 8, "%u", m_port);
    config.set(CONFIG_OPTIONS[ConfigPort].name, buffer);

    if(!config.save())
        _Module.log().vlogln(LogOutputWarning, "Could not save configuration: %s", EnergonSoftware::last_error().c_str());

	EndDialog(wID);
    return 0;
}


LRESULT CConnectDlg::OnDefaultCmd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
    m_server = "localhost";
    m_port = APP_PORT;

    DoDataExchange();

    return 0;
}


LRESULT CConnectDlg::OnCancelCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/)
{
    EndDialog(wID);
    return 0;
}
