/*
====================
File: WinAmpControl.h
Author: Shane Lillie
Description: WinAmpControl module header.

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

#if !defined __WINAMPCONTROL_H__
#define __WINAMPCONTROL_H__

#if _MSC_VER >= 1000
#pragma once
#endif

#include <string>


/*
 *  constants
 *
 */


enum WinAmpControlCD
{
    WinAmpControlCD1=0x01,
    WinAmpControlCD2,
    WinAmpControlCD3,
    WinAmpControlCD4,
};


/*
class WinAmpControl
*/
class WinAmpControl
{
public:
    WinAmpControl();

public:
    // execs/closes/resets WinAmp
    bool exec();
    void close();
    void reset();

    // controls WinAmp
    void play();
    void play_cd(WinAmpControlCD cdnumber);
    void pause();
    void stop();
    void prev_song();
    void next_song();
    void ffw_5s();   // fast-forward 5 seconds
    void rew_5s();   // rewind 5 seconds

    // volume/panning control
    void volume_set(byte volume);
    void volume_up();
    void volume_down();
    void panning_set(byte panning);

    // shuffle/repeat control
    void shuffle_set(bool shuffle);
    bool shuffle_get();
    void repeat_set(bool repeat);
    bool repeat_get();

    // playlist controls
    //void load_playlist(const std::string& playlist);

    // returns true if WinAmp
    // is currently running
    // NOTE: this updates the
    // m_hWnd member variable
    bool running();

    // returns the WinAmp version
    // or -1 if it's not running
    int version();

public:
    void set_path(const std::string& path)
    {
        m_path = path;
    }

    void reset_path()
    {
        m_path = DEFAULT_WINAMP_PATH;
    }

    const std::string& path() const
    {
        return m_path;
    }

private:
    bool get_window();
    LRESULT send_winamp_control(LPARAM command, WPARAM parameter=0);            // WM_WA_IPC
    LRESULT send_winamp_copydata(ULONG_PTR dwData, PVOID lpData, size_t size);  // WM_COPYDATA (size = sizeof(lpData)
    LRESULT send_winamp_command(WPARAM command);                                // WM_COMMAND

private:
    HWND m_hWnd;
    std::string m_path;
};


#endif