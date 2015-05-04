/*
====================
File: WACApplication.h
Author: Shane Lillie
Description: WACApplication module header.

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


#if !defined __WACAPPLICATION_H__
#define __WACAPPLICATION_H__

#if _MSC_VER >= 1000
#pragma once
#endif

#include "EnRunnableApplication.h"
#include "EnSocket.h"

//#include "MainDlg.h"


/*
class WACApplication
*/
class WACApplication : public EnRunnableApplication
{
public:
    enum DisconnectMethod
    {
        DisconnectServer,       // server says to go
        DisconnectClient,       // client says to go
        DisconnectError,        // internal error, do disconnect
        DisconnectFatalError    // internal error, don't disconnect
    };

public:
    WACApplication();

public:
    bool connect();
    void disconnect(DisconnectMethod method=DisconnectClient);
    bool send_packet(const EnPacket& packet);

    void handle_events();

    bool winamp_exec();
    bool winamp_close();
    bool winamp_reset();
    bool winamp_play();
    bool winamp_pause();
    bool winamp_stop();
    bool winamp_prev();
    bool winamp_next();

public:
    // since this is a Windows app, pass
    // nShowCmd to argc and lpstrCmdLine
    // as a single dimension array to argv
    virtual int run(int argc, char* argv[]);

public:
    bool connected() const
    {
        return m_socket.valid();
    }

    EnLog& log()
    {
        return m_log;
    }

    EnConfig& config()
    {
        return m_config;
    }

private:
    bool handle_packet(EnPacket& packet);

    void default_config();
    void redirect_log(const std::string& filename);

    void display_warning(int id, const std::string& message);
    void display_error(int id, const std::string& message, bool disconnect=true);
    void display_socket_error(int id, const std::string& message, bool disconnect=true);
    void send_packet_error();

    bool send_winamp_packet(PacketType type);

private:
    //CMainDlg m_main_dialog;
    EnClientSocket m_socket;
};


/*
 *  external globals
 *
 */


extern WACApplication g_application;


#endif
