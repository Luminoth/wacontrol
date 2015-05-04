/*
====================
File: ShellNotifyIcon.h
Author: Shane Lillie
Description: CShellNotifyIcon module header.

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

#if !defined __SHELLNOTIFYICON_H__
#define __SHELLNOTIFYICON_H__

#if _MSC_VER >= 1000
#pragma once
#endif

#include <cstring>
#include <string>


/*
class CShellNotifyIcon
*/
template<class T>
class CShellNotifyIcon : public CWindowImpl<T>
{
public:
    CShellNotifyIcon<T>()
        : CWindowImpl<T>()
    {
    }

public:
    bool AddIcon(HWND hWnd, UINT uID, HICON hIcon, const std::string& tip=std::string())
    {
        NOTIFYICONDATA nid;
        ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = hWnd;
        nid.uID = uID;
        nid.uFlags = NIF_ICON;
        nid.hIcon = hIcon;

        if(!tip.empty()) {
            nid.uFlags |= NIF_TIP;
            std::strncpy(nid.szTip, tip.c_str(), 64);
        }
        return static_cast<bool>(Shell_NotifyIcon(NIM_ADD, &nid));
    }

    bool AddIconMessage(HWND hWnd, UINT uID, HICON hIcon, UINT uCallbackMessage, const std::string& tip=std::string())
    {
        NOTIFYICONDATA nid;
        ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = hWnd;
        nid.uID = uID;
        nid.uFlags = NIF_ICON | NIF_MESSAGE;
        nid.hIcon = hIcon;
        nid.uCallbackMessage = uCallbackMessage;

        if(!tip.empty()) {
            nid.uFlags |= NIF_TIP;
            std::strncpy(nid.szTip, tip.c_str(), 64);
        }
        return static_cast<bool>(Shell_NotifyIcon(NIM_ADD, &nid));
    }

    bool DeleteIcon(HWND hWnd, UINT uID)
    {
        NOTIFYICONDATA nid;
        ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = hWnd;
        nid.uID = uID;

        return static_cast<bool>(Shell_NotifyIcon(NIM_DELETE, &nid));
    }
};


#endif
