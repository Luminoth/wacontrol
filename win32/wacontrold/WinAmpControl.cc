/*
====================
File: WinAmpControl.cc
Author: Shane Lillie
Description: WinAmpControl module soiurce.

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

#include "wa_ipc.h"

#include "WinAmpControl.h"


/*
 *  WinAmpControl methods
 *
 */


WinAmpControl::WinAmpControl()
    :   m_hWnd(NULL), m_path(DEFAULT_WINAMP_PATH)
{
}


bool WinAmpControl::exec()
{
    if(running()) {
        _Module.log().logln("WinAmp is already running...");
        return true;
    }
    return reinterpret_cast<int>(ShellExecute(NULL, "open", m_path.c_str(), NULL, NULL, SW_SHOWNORMAL)) > 32;
}


void WinAmpControl::close()
{
    if(!running())
        return;

    SendMessage(m_hWnd, WM_CLOSE, 0, 0);
    m_hWnd = NULL;
}


void WinAmpControl::reset()
{
    if(!running())
        return;

    send_winamp_control(IPC_RESTARTWINAMP);
}


void WinAmpControl::play()
{
    if(!running())
        return;

    send_winamp_command(WINAMP_BUTTON2);
}


void WinAmpControl::play_cd(WinAmpControlCD cdnumber)
{
    if(!running())
        return;

    WPARAM parameter;
    switch(cdnumber)
    {
    case WinAmpControlCD1:
        parameter = ID_MAIN_PLAY_AUDIOCD1;
        break;
    case WinAmpControlCD2:
        parameter = ID_MAIN_PLAY_AUDIOCD2;
        break;
    case WinAmpControlCD3:
        parameter = ID_MAIN_PLAY_AUDIOCD3;
        break;
    case WinAmpControlCD4:
        parameter = ID_MAIN_PLAY_AUDIOCD4;
        break;
    }

    send_winamp_command(parameter);
}


void WinAmpControl::pause()
{
    if(!running())
        return;

    send_winamp_command(WINAMP_BUTTON3);
}


void WinAmpControl::stop()
{
    if(!running())
        return;

    send_winamp_command(WINAMP_BUTTON4);
}


void WinAmpControl::prev_song()
{
    if(!running())
        return;

    send_winamp_command(WINAMP_BUTTON1);
}


void WinAmpControl::next_song()
{
    if(!running())
        return;

    send_winamp_command(WINAMP_BUTTON5);
}


void WinAmpControl::ffw_5s()
{
    if(!running())
        return;

    send_winamp_command(WINAMP_FFWD5S);
}


void WinAmpControl::rew_5s()
{
    if(!running())
        return;

    send_winamp_command(WINAMP_REW5S);
}


void WinAmpControl::volume_set(byte volume)
{
    if(!running())
        return;

    send_winamp_control(IPC_SETVOLUME, volume);
}


void WinAmpControl::volume_up()
{
    if(!running())
        return;

    send_winamp_command(WINAMP_VOLUMEUP);
}


void WinAmpControl::volume_down()
{
    if(!running())
        return;

    send_winamp_command(WINAMP_VOLUMEDOWN);
}


void WinAmpControl::panning_set(byte panning)
{
    if(!running())
        return;

    send_winamp_control(IPC_SETPANNING, panning);
}


void WinAmpControl::shuffle_set(bool shuffle)
{
    if(!running())
        return;

    send_winamp_control(IPC_SET_SHUFFLE, shuffle ? 1 : 0);
}


bool WinAmpControl::shuffle_get()
{
    if(!running())
        return false;

    return static_cast<bool>(send_winamp_control(IPC_GET_SHUFFLE));
}


void WinAmpControl::repeat_set(bool repeat)
{
    if(!running())
        return;

    send_winamp_control(IPC_SET_REPEAT, repeat ? 1 : 0);
}


bool WinAmpControl::repeat_get()
{
    if(!running())
        return false;

    return static_cast<bool>(send_winamp_control(IPC_GET_REPEAT));
}

#if 0
void WinAmpControl::load_playlist(const std::string& playlist)
{
/* TODO: this doesn't work! */

    // clear the playlist
    //send_winamp_control(IPC_DELETE);

    char buffer[MAX_PATH];
    std::strncpy(buffer, playlist.c_str(), MAX_PATH);

    // load the new list
    send_winamp_control(IPC_CHANGECURRENTFILE, reinterpret_cast<WPARAM>(buffer));
}
#endif

bool WinAmpControl::running()
{
    return get_window();
}


int WinAmpControl::version()
{
    if(!running()) return false;
    return static_cast<int>(SendMessage(m_hWnd, WM_WA_IPC, 0, IPC_GETVERSION));
}


bool WinAmpControl::get_window()
{
    m_hWnd = FindWindow("Winamp v1.x", NULL);
    return m_hWnd != NULL;
}


LRESULT WinAmpControl::send_winamp_control(LPARAM command, WPARAM parameter)
{
    if(!running())
        return 0;

    return SendMessage(m_hWnd, WM_WA_IPC, parameter, command);
}


LRESULT WinAmpControl::send_winamp_copydata(ULONG_PTR dwData, PVOID lpData, size_t size)
{
    COPYDATASTRUCT cpds;
    cpds.dwData = dwData;
    cpds.cbData = size;
    cpds.lpData = lpData;

    return SendMessage(m_hWnd, WM_COPYDATA, NULL, reinterpret_cast<LPARAM>(&cpds));
}


LRESULT WinAmpControl::send_winamp_command(WPARAM command)
{
    if(!running())
        return 0;

    return SendMessage(m_hWnd, WM_COMMAND, command, 0);
}