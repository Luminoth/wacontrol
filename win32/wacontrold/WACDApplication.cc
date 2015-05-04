/*
====================
File: WACDApplication.cc
Author: Shane Lillie
Description: CWACDApplication module source.

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

#include <cstdlib>

#include "EnFunctions.h"
#include "EnPacket.h"

#include "MyMessageLoop.h"


/*
 *  globals
 *
 */


CWACDApplication _Module;


/*
 *  functions
 *
 */


bool invalid_client_socket(const EnClientSocket& cs)
{
    return !cs.valid();
}


/*
 *  CWACDApplication methods
 *
 */


CWACDApplication::CWACDApplication()
    : CAppModule(), EnApplication(),
        EnRunner(), m_maxsocket(-1)
{
    m_config.filename(DEFAULT_CONFIG);
    redirect_log(DEFAULT_LOG);
}


bool CWACDApplication::send_packet(EnClientSocket& socket, const EnPacket& packet)
{
    // this won't be an error
    // so just ignore it
    if(!socket.valid())
        return true;

    if(!socket.send(packet)) {
        send_packet_error();
        return false;
    }
    return true;
}


void CWACDApplication::handle_events()
{
    if(!valid())
        return;

    calculate_maxsocket();

    EnSocketSet readset, exceptset;
    readset = exceptset = m_sockets;

    // 500 microsecond timeout
    static timeval tv = { 0, 500 };

    if(readset.select(m_maxsocket, exceptset, EnSocketSet::SelectRead, &tv) == SOCKET_ERROR) {
        display_socket_error(IDS_ERR_SELECT, "Error selecting sockets");
        return;
    }

    if(readset.is_set(m_socket))
        accept_connection();

    handle_clients(readset, exceptset);
}


void CWACDApplication::quit()
{
    m_main_dialog.SendMessage(WM_COMMAND, MAKEWPARAM(IDR_TRAY_MENU, 0));
}


int CWACDApplication::run()
{
/* TODO: bring up first time configuration if needed */
    m_config.set_header(CONFIG_HEADER);
    m_config.set_defaults(CONFIG_OPTIONS);
    m_config.load_defaults();

    m_log.vlogln(LogOutputNormal, "Loading configuration from '%s'...", m_config.filename().c_str());
    if(!m_config.load()) {
        m_log.vlogln(LogOutputWarning, "Error loading configuration: %s", EnergonSoftware::last_std_error().c_str());
        AtlMessageBox(NULL, IDS_ERR_LOAD_CONFIG, IDR_MAINFRAME, MB_OK | MB_ICONWARNING);
    }
    m_config.changed(false);

    m_log.logln("Server starting...");
    if(!EnServerSocket::create_server_socket(m_socket, AF_INET, SOCK_STREAM, APP_PORT)) {
        display_socket_error(IDS_ERR_CONNECT, "Could not create server socket", false);     
        return 1;
    }

    m_sockets.set(m_socket);

	CMyMessageLoop theLoop;
	AddMessageLoop(&theLoop);

	if(m_main_dialog.Create(NULL) == NULL) {
        m_log.vlogln(LogOutputError, "Could not create main dialog: %s", EnergonSoftware::last_error().c_str());
        AtlMessageBox(NULL, IDS_ERR_CREATE_WINDOW, IDR_MAINFRAME, MB_OK | MB_ICONERROR);
		return 0;
	}

	m_main_dialog.ShowWindow(SW_HIDE);
    m_main_dialog.UpdateWindow();

	int nRet = theLoop.Run();

	RemoveMessageLoop();

    disconnect_all_clients();

    m_socket.shutdown();
    m_socket.close();

    if(!m_config.save()) {
        m_log.vlogln(LogOutputWarning, "Error saving configuration: %s", EnergonSoftware::last_std_error().c_str());
        AtlMessageBox(NULL, IDS_ERR_SAVE_CONFIG, IDR_MAINFRAME, MB_OK | MB_ICONWARNING);
    }

	return nRet;
}


void CWACDApplication::calculate_maxsocket()
{
    m_maxsocket = m_socket.socket();
    for(Clients::const_iterator it = m_clients.begin(); it != m_clients.end(); ++it)
        if(it->socket() > m_maxsocket)
            m_maxsocket = it->socket();
    m_maxsocket++;
}


void CWACDApplication::accept_connection()
{
    EnClientSocket cs(m_socket.accept());
    if(!cs.valid()) return;

    m_log.vlogln(LogOutputNormal, "Accepted a new connection on %u...", cs.socket());

    m_sockets.set(cs);
    m_clients.push_back(cs);
}


void CWACDApplication::disconnect_client(EnClientSocket& socket)
{
    EnPacket packet;
    packet.pack_byte(PacketDisconnect);
    send_packet(socket, packet);
}


void CWACDApplication::disconnect_client(Clients::iterator& it, bool send)
{
    m_log.vlogln(LogOutputNormal, "Disconnecting %d...", it->socket());

    if(send) disconnect_client(*it);

    m_sockets.clear(*it);
    it->shutdown();
    it->close();
}


void CWACDApplication::disconnect_all_clients()
{
    m_log.logln("Disconnecting all clients...");

    for(Clients::iterator it = m_clients.begin(); it != m_clients.end(); ++it)
        disconnect_client(it);
}


bool CWACDApplication::handle_packet(EnPacket& packet, Clients::iterator& it)
{
    byte header;
    if(!packet.unpack_byte(header)) {
        m_log.log("Invalid packet header recieved: ", LogOutputError);
        m_log << packet;
        m_log.logln();
        return false;
    }

    switch(header)
    {
    case PacketDisconnect:
        disconnect_client(it, false);
        break;
    case PacketWinAmpExec:
        if(!winamp_exec())
            quit();
        break;
    case PacketWinAmpClose:
        winamp_close();
        break;
    case PacketWinAmpReset:
        winamp_reset();
        break;
    case PacketWinAmpPlay:
        winamp_play();
        break;
    case PacketWinAmpPlayCD:
        if(!winamp_play_cd(packet))
            disconnect_client(it);
    case PacketWinAmpPause:
        winamp_pause();
        break;
    case PacketWinAmpStop:
        winamp_stop();
        break;
    case PacketWinAmpPrev:
        winamp_prev();
        break;
    case PacketWinAmpNext:
        winamp_next();
        break;
    case PacketWinAmpFFw5:
        winamp_ffw_5s();
        break;
    case PacketWinAmpRew5:
        winamp_rew_5s();
        break;
    case PacketWinAmpVolumeSet:
        if(!winamp_volume_set(packet))
            disconnect_client(it);
        break;
    case PacketWinAmpVolumeUp:
        winamp_volume_up();
        break;
    case PacketWinAmpVolumeDown:
        winamp_volume_down();
        break;
    case PacketWinAmpPanningSet:
        if(!winamp_panning_set(packet))
            disconnect_client(it);
        break;
    case PacketWinAmpShuffleSet:
        if(!winamp_shuffle_set(packet))
            disconnect_client(it);
        break;
    case PacketWinAmpRepeatSet:
        if(!winamp_repeat_set(packet))
            disconnect_client(it);
        break;
    /*case PacketWinAmpLoad:
        if(!winamp_load(packet))
            quit();
        break;*/
    default:
        m_log.vlogln(LogOutputError, "Invalid packet header: %d", static_cast<int>(header));
        return false;
    }

    return true;
}


void CWACDApplication::handle_clients(const EnSocketSet& readset, const EnSocketSet& exceptset)
{
    EnPacket packet;
    for(Clients::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
        if(readset.is_set(*it)) {
            if(!it->recv(packet)) {
                display_socket_error(IDS_ERR_RECVPACKET, "Error recieving packet", false);
                disconnect_client(it);
                packet.erase(); // just in case
                continue;
            }

            if(!handle_packet(packet, it))
                disconnect_client(it);
            packet.erase();
        } else if(exceptset.is_set(*it)) {
            m_log.logln("Client found in except set, removing...", LogOutputWarning);
            disconnect_client(it, false);
        }
    }
    m_clients.remove_if(invalid_client_socket);
}


void CWACDApplication::redirect_log(const std::string& filename)
{
    char msg[256];
    CString buffer;

    if(!m_log.redirect(filename)) {
        AtlLoadString(IDS_ERR_LOG_REDIRECT, msg, 256);
        buffer.Format(msg, EnergonSoftware::last_error().c_str());
        AtlMessageBox(NULL, static_cast<const char*>(buffer), IDR_MAINFRAME, MB_OK | MB_ICONWARNING);
    }
}


void CWACDApplication::display_warning(int id, const std::string& message)
{
    CString buffer;
    buffer.Format("%s: %s", message.c_str(), EnergonSoftware::last_error().c_str());

    m_log.logln(static_cast<const char*>(buffer), LogOutputWarning);
    AtlMessageBox(m_main_dialog, id, IDR_MAINFRAME, MB_OK | MB_ICONWARNING);
}


void CWACDApplication::display_error(int id, const std::string& message, bool quit)
{
    CString buffer;
    buffer.Format("%s: %s", message.c_str(), EnergonSoftware::last_error().c_str());

    m_log.logln(static_cast<const char*>(buffer), LogOutputError);
    AtlMessageBox(m_main_dialog, id, IDR_MAINFRAME, MB_OK | MB_ICONERROR);

    if(quit) this->quit();
}


void CWACDApplication::display_socket_error(int id, const std::string& message, bool quit)
{
    CString buffer;
    buffer.Format("%s: %s", message.c_str(), EnergonSoftware::last_error(EnSocket::last_socket_error()).c_str());

    m_log.logln(static_cast<const char*>(buffer), LogOutputError);
    AtlMessageBox(m_main_dialog, id, IDR_MAINFRAME, MB_OK | MB_ICONERROR);

    if(quit) this->quit();
}


void CWACDApplication::send_packet_error()
{
    display_error(IDS_ERR_SENDPACKET, "Error sending packet");
}


bool CWACDApplication::winamp_exec()
{
    m_winamp_control.set_path(m_config.lookup(CONFIG_OPTIONS[ConfigPath].name));

    m_log.vlogln(LogOutputNormal, "Executing WinAmp at %s...", m_winamp_control.path().c_str());

    if(!m_winamp_control.exec()) {
        m_log.vlogln(LogOutputError, "Could not execute WinAmp: %s", EnergonSoftware::last_error().c_str());
        return false;
    }
    return true;
}


void CWACDApplication::winamp_close()
{
    m_log.logln("Closing WinAmp...");

    m_winamp_control.close();
}


void CWACDApplication::winamp_reset()
{
    m_log.logln("Resetting WinAmp...");

    m_winamp_control.reset();
}


void CWACDApplication::winamp_play()
{
    m_log.logln("Playing song...");

    m_winamp_control.play();
}


bool CWACDApplication::winamp_play_cd(EnPacket& packet)
{
    byte cdnumber;
    if(!packet.unpack_byte(cdnumber)) {
        m_log.log("Invalid packet recieved: ", LogOutputError);
        m_log << packet;
        m_log.logln();
        return false;
    }

    switch(cdnumber)
    {
    case 1:
        m_log.logln("Playing CD 1...");
        m_winamp_control.play_cd(WinAmpControlCD1);
        break;
    case 2:
        m_log.logln("Playing CD 2...");
        m_winamp_control.play_cd(WinAmpControlCD2);
        break;
    case 3:
        m_log.logln("Playing CD 3...");
        m_winamp_control.play_cd(WinAmpControlCD3);
        break;
    case 4:
        m_log.logln("Playing CD 4...");
        m_winamp_control.play_cd(WinAmpControlCD4);
        break;
    default:
        m_log.vlogln(LogOutputWarning, "Invalid CD number: %d", static_cast<int>(cdnumber));
        return false;
    }

    return true;
}


void CWACDApplication::winamp_pause()
{
    m_log.logln("Pausing song...");

    m_winamp_control.pause();
}


void CWACDApplication::winamp_stop()
{
    m_log.logln("Stopping song...");

    m_winamp_control.stop();
}


void CWACDApplication::winamp_prev()
{
    m_log.logln("Playing previous song...");

    m_winamp_control.prev_song();
}


void CWACDApplication::winamp_next()
{
    m_log.logln("Playing next song...");

    m_winamp_control.next_song();
}


void CWACDApplication::winamp_ffw_5s()
{
    m_log.logln("Fast-forwarding 5 seconds...");

    m_winamp_control.ffw_5s();
}


void CWACDApplication::winamp_rew_5s()
{
    m_log.logln("Rewinding 5 seconds...");

    m_winamp_control.rew_5s();
}



bool CWACDApplication::winamp_volume_set(EnPacket& packet)
{
    byte volume;
    if(!packet.unpack_byte(volume)) {
        m_log.log("Invalid packet recieved: ", LogOutputError);
        m_log << packet;
        m_log.logln();
        return false;
    }

    m_log.vlogln(LogOutputNormal, "Setting volume to %d...", static_cast<int>(volume));

    m_winamp_control.volume_set(volume);

    return true;
}


void CWACDApplication::winamp_volume_up()
{
    m_log.logln("Increasing volume...");

    m_winamp_control.volume_up();
}


void CWACDApplication::winamp_volume_down()
{
    m_log.logln("Lowering volume...");

    m_winamp_control.volume_down();
}


bool CWACDApplication::winamp_panning_set(EnPacket& packet)
{
    byte panning;
    if(!packet.unpack_byte(panning)) {
        m_log.log("Invalid packet recieved: ", LogOutputError);
        m_log << packet;
        m_log.logln();
        return false;
    }

    m_log.vlogln(LogOutputNormal, "Setting panning to %d...", static_cast<int>(panning));

    m_winamp_control.panning_set(panning);

    return true;
}


bool CWACDApplication::winamp_shuffle_set(EnPacket& packet)
{
    byte shuffle;
    if(!packet.unpack_byte(shuffle)) {
        m_log.log("Invalid packet recieved: ", LogOutputError);
        m_log << packet;
        m_log.logln();
        return false;
    }

    m_log.vlogln(LogOutputNormal, "Setting shuffle to %s...", shuffle ? "on" : "off");

    m_winamp_control.shuffle_set(static_cast<bool>(shuffle));

    return true;
}


bool CWACDApplication::winamp_repeat_set(EnPacket& packet)
{
    byte repeat;
    if(!packet.unpack_byte(repeat)) {
        m_log.log("Invalid packet recieved: ", LogOutputError);
        m_log << packet;
        m_log.logln();
        return false;
    }

    m_log.vlogln(LogOutputNormal, "Setting repeat to %s...", repeat ? "on" : "off");

    m_winamp_control.repeat_set(static_cast<bool>(repeat));

    return true;
}

#if 0
bool CWACDApplication::winamp_load(EnPacket& packet)
{
    std::string playlist;
    if(!packet.unpack_string(playlist)) {
        m_log.log("Invalid packet recieved: ", LogOutputError);
        m_log << packet;
        m_log.logln();
        return false;
    }

    m_log.vlogln(LogOutputNormal, "Loading playlist %s...", playlist.c_str());

    m_winamp_control.load_playlist(playlist);

    return true;
}
#endif
