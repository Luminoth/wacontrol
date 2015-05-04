/*
====================
File: WACDApplication.h
Author: Shane Lillie
Description: CWACApplication module header.

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


#if !defined __WACDAPPLICATION_H__
#define __WACDAPPLICATION_H__

#if _MSC_VER >= 1000
#pragma once
#endif

#include <list>

#include "EnApplication.h"
#include "EnRunner.h"
#include "EnSocket.h"
#include "EnSocketSet.h"

#include "MainDlg.h"
#include "WinAmpControl.h"


/*
 *  typedefs
 *
 */


typedef std::list<EnClientSocket> Clients;


/*
class CWACDApplication
*/
class CWACDApplication : public CAppModule, public EnApplication, public EnRunner
{
public:
    CWACDApplication();

public:
    bool send_packet(EnClientSocket& socket, const EnPacket& packet);
    void handle_events();
    void quit();

public:
    virtual int run();

public:
    bool valid() const
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

    size_t client_count() const
    {
        return m_clients.size();
    }

private:
    void calculate_maxsocket();
    void accept_connection();
    void disconnect_client(EnClientSocket& socket);
    void disconnect_client(Clients::iterator& it, bool send=true);
    void disconnect_all_clients();

    bool handle_packet(EnPacket& packet, Clients::iterator& it);
    void handle_clients(const EnSocketSet& readset, const EnSocketSet& exceptset);

    void redirect_log(const std::string& filename);

    void display_warning(int id, const std::string& message);
    void display_error(int id, const std::string& message, bool quit=true);
    void display_socket_error(int id, const std::string& message, bool quit=true);
    void send_packet_error();

    bool winamp_exec();
    void winamp_close();
    void winamp_reset();
    void winamp_play();
    bool winamp_play_cd(EnPacket& packet);
    void winamp_pause();
    void winamp_stop();
    void winamp_prev();
    void winamp_next();
    void winamp_ffw_5s();
    void winamp_rew_5s();
    bool winamp_volume_set(EnPacket& packet);
    void winamp_volume_up();
    void winamp_volume_down();
    bool winamp_panning_set(EnPacket& packet);
    bool winamp_shuffle_set(EnPacket& packet);
    bool winamp_repeat_set(EnPacket& packet);
    //bool winamp_load(EnPacket& packet);

private:
    CMainDlg m_main_dialog;
    WinAmpControl m_winamp_control;
    EnServerSocket m_socket;
    EnSocketSet m_sockets;
    int m_maxsocket;

    Clients m_clients;
};


/*
 *  external globals
 *
 */


extern CWACDApplication _Module;


#endif
