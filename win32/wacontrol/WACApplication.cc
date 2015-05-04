/*
====================
File: WACApplication.cc
Author: Shane Lillie
Description: CWACApplication module source.

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
#include "EnSocketSet.h"
#include "EnPacket.h"

#include "MyMessageLoop.h"


/*
 *  globals
 *
 */


CWACApplication _Module;


/*
 *  CWACApplication methods
 *
 */


CWACApplication::CWACApplication()
    : CAppModule(), EnApplication(),
        EnRunner()
{
    m_config.filename(DEFAULT_CONFIG);
    redirect_log(DEFAULT_LOG);
}


void CWACApplication::arguments(int argc, char* argv[])
{
    m_show_cmd = argc;
}


bool CWACApplication::connect()
{
    if(connected())
        return true;

    CWaitCursor wc;

    const std::string& server(m_config.lookup(CONFIG_OPTIONS[ConfigServer].name));
    unsigned short port(std::atoi(m_config.lookup(CONFIG_OPTIONS[ConfigPort].name).c_str()));

    m_log.vlogln(LogOutputNormal, "Attempting to connect to %s:%u...", server.c_str(), port);

    if(!EnClientSocket::create_client_socket(m_socket, AF_INET, SOCK_STREAM, server, port)) {
        display_socket_error(IDS_ERR_CONNECT, "Could not create client socket", false);
        disconnect(DisconnectFatalError);
        return false;
    }

    return true;
}


void CWACApplication::disconnect(DisconnectMethod method)
{
    if(!connected())
        return;

    CWaitCursor wc;

    std::string scratch;
    switch(method)
    {
    case DisconnectServer:
        m_log.logln("Server disconnected!", LogOutputError);
        AtlMessageBox(m_main_dialog, IDS_ERR_SERVER_DISCONNECTED, IDR_MAINFRAME, MB_OK | MB_ICONERROR);
        break;
    case DisconnectClient:
        m_log.logln("Disconnecting...");
        break;
    case DisconnectError:
    case DisconnectFatalError:
        m_log.logln("Forcing disconnect...", LogOutputWarning);
        break;
    }

    if(method != DisconnectServer && method != DisconnectFatalError) {
        EnPacket packet;
        packet.pack_byte(PacketDisconnect);
        send_packet(packet);
    }

    m_socket.shutdown();
    m_socket.close();
}


bool CWACApplication::send_packet(const EnPacket& packet)
{
    if(!m_socket.send(packet)) {
        send_packet_error();
        return false;
    }
    return true;
}


void CWACApplication::handle_events()
{
    if(!connected())
        return;

    EnSocketSet fds;
    fds.set(m_socket);

    // 500 microsecond timeout
    static timeval tv = { 0, 500 };

    if(fds.select(m_socket.socket() + 1, EnSocketSet::SelectRead, &tv) == SOCKET_ERROR) {
        display_socket_error(IDS_ERR_SELECT, "Error selecting sockets");
        return;
    }

    if(fds.is_set(m_socket)) {
        EnPacket packet;
        if(m_socket.recv(packet) <= 0) {
            display_socket_error(IDS_ERR_RECVPACKET, "Error recieving packet");
            return;
        }

        if(!handle_packet(packet))
            disconnect(DisconnectError);
    }
}


bool CWACApplication::winamp_exec()
{
    return send_winamp_packet(PacketWinAmpExec);
}


bool CWACApplication::winamp_close()
{
    return send_winamp_packet(PacketWinAmpClose);
}


bool CWACApplication::winamp_reset()
{
    return send_winamp_packet(PacketWinAmpReset);
}


bool CWACApplication::winamp_play()
{
    return send_winamp_packet(PacketWinAmpPlay);
}


bool CWACApplication::winamp_play_cd(byte cdnumber)
{
    EnPacket packet;
    packet.pack_byte(PacketWinAmpPlayCD);
    packet.pack_byte(cdnumber);

    if(!send_packet(packet)) {
        send_packet_error();
        return false;
    }

    return true;
}


bool CWACApplication::winamp_pause()
{
    return send_winamp_packet(PacketWinAmpPause);
}


bool CWACApplication::winamp_stop()
{
    return send_winamp_packet(PacketWinAmpStop);
}


bool CWACApplication::winamp_prev()
{
    return send_winamp_packet(PacketWinAmpPrev);
}


bool CWACApplication::winamp_next()
{
    return send_winamp_packet(PacketWinAmpNext);
}


bool CWACApplication::winamp_ffw5s()
{
    return send_winamp_packet(PacketWinAmpFFw5);
}


bool CWACApplication::winamp_rew5s()
{
    return send_winamp_packet(PacketWinAmpRew5);
}


bool CWACApplication::winamp_volume_set(byte volume)
{
    EnPacket packet;
    packet.pack_byte(PacketWinAmpVolumeSet);
    packet.pack_byte(volume);

    if(!send_packet(packet)) {
        send_packet_error();
        return false;
    }

    return true;
}


bool CWACApplication::winamp_volume_up()
{
    return send_winamp_packet(PacketWinAmpVolumeUp);
}


bool CWACApplication::winamp_volume_down()
{
    return send_winamp_packet(PacketWinAmpVolumeDown);
}


bool CWACApplication::winamp_panning_set(byte panning)
{
    EnPacket packet;
    packet.pack_byte(PacketWinAmpPanningSet);
    packet.pack_byte(panning);

    if(!send_packet(packet)) {
        send_packet_error();
        return false;
    }

    return true;
}


bool CWACApplication::winamp_shuffle_set(bool shuffle)
{
    EnPacket packet;
    packet.pack_byte(PacketWinAmpShuffleSet);
    packet.pack_byte(static_cast<byte>(shuffle));

    if(!send_packet(packet)) {
        send_packet_error();
        return false;
    }

    return true;
}


bool CWACApplication::winamp_repeat_set(bool repeat)
{
    EnPacket packet;
    packet.pack_byte(PacketWinAmpRepeatSet);
    packet.pack_byte(static_cast<byte>(repeat));

    if(!send_packet(packet)) {
        send_packet_error();
        return false;
    }

    return true;
}


#if 0
bool CWACApplication::winamp_load(const CString& playlist)
{
    EnPacket packet;
    packet.pack_byte(PacketWinAmpLoad);
    packet.pack_string(static_cast<const char*>(playlist));

    if(!send_packet(packet)) {
        send_packet_error();
        return false;
    }

    return true;
}
#endif

int CWACApplication::run()
{
    m_config.set_header(CONFIG_HEADER);
    m_config.set_defaults(CONFIG_OPTIONS);
    m_config.load_defaults();

    m_log.vlogln(LogOutputNormal, "Loading configuration from '%s'...", m_config.filename().c_str());
    if(!m_config.load()) {
        m_log.vlogln(LogOutputWarning, "Error loading configuration: %s", EnergonSoftware::last_std_error().c_str());
        AtlMessageBox(NULL, IDS_ERR_LOAD_CONFIG, IDR_MAINFRAME, MB_OK | MB_ICONWARNING);
    }
    m_config.changed(false);

	CMyMessageLoop theLoop;
	AddMessageLoop(&theLoop);

	if(m_main_dialog.Create(NULL) == NULL) {
        m_log.vlogln(LogOutputError, "Could not create main dialog: %s", EnergonSoftware::last_error().c_str());
        AtlMessageBox(NULL, IDS_ERR_CREATE_WINDOW, IDR_MAINFRAME, MB_OK | MB_ICONERROR);
		return 0;
	}

	m_main_dialog.ShowWindow(m_show_cmd);
    m_main_dialog.UpdateWindow();

	int nRet = theLoop.Run();

    disconnect();
	RemoveMessageLoop();

    if(!m_config.save()) {
        m_log.vlogln(LogOutputWarning, "Error saving configuration: %s", EnergonSoftware::last_std_error().c_str());
        AtlMessageBox(NULL, IDS_ERR_SAVE_CONFIG, IDR_MAINFRAME, MB_OK | MB_ICONWARNING);
    }

	return nRet;
}


bool CWACApplication::handle_packet(EnPacket& packet)
{
    byte header;
    if(!packet.unpack_byte(header)) {
        m_log.log("Invalid packet header recieved: ", LogOutputError);
        m_log << packet;
        m_log.logln();

        AtlMessageBox(m_main_dialog, IDS_ERR_PACKET, IDR_MAINFRAME, MB_OK | MB_ICONERROR);
        return false;
    }

    switch(header)
    {
    case PacketDisconnect:
        disconnect(DisconnectServer);
        break;
    default:
        m_log.vlogln(LogOutputError, "Invalid packet type: %d", static_cast<int>(header));
        AtlMessageBox(m_main_dialog, IDS_ERR_PACKET, IDR_MAINFRAME, MB_OK | MB_ICONERROR);
        return false;
    }

    return true;
}


void CWACApplication::redirect_log(const std::string& filename)
{
    char msg[256];
    CString buffer;

    if(!m_log.redirect(filename)) {
        AtlLoadString(IDS_ERR_LOG_REDIRECT, msg, 256);
        buffer.Format(msg, EnergonSoftware::last_error().c_str());
        AtlMessageBox(NULL, static_cast<const char*>(buffer), IDR_MAINFRAME, MB_OK | MB_ICONWARNING);
    }
}


void CWACApplication::display_warning(int id, const std::string& message)
{
    CString buffer;
    buffer.Format("%s: %s", message.c_str(), EnergonSoftware::last_error().c_str());

    m_log.logln(static_cast<const char*>(buffer), LogOutputWarning);
    AtlMessageBox(m_main_dialog, id, IDR_MAINFRAME, MB_OK | MB_ICONWARNING);
}


void CWACApplication::display_error(int id, const std::string& message, bool disconnect)
{
    CString buffer;
    buffer.Format("%s: %s", message.c_str(), EnergonSoftware::last_error().c_str());

    m_log.logln(static_cast<const char*>(buffer), LogOutputError);
    AtlMessageBox(m_main_dialog, id, IDR_MAINFRAME, MB_OK | MB_ICONERROR);

    if(disconnect) this->disconnect(DisconnectError);
}


void CWACApplication::display_socket_error(int id, const std::string& message, bool disconnect)
{
    CString buffer;
    buffer.Format("%s: %s", message.c_str(), EnergonSoftware::last_error(EnSocket::last_socket_error()).c_str());

    m_log.logln(static_cast<const char*>(buffer), LogOutputError);
    AtlMessageBox(m_main_dialog, id, IDR_MAINFRAME, MB_OK | MB_ICONERROR);

    if(disconnect) this->disconnect(DisconnectError);
}


void CWACApplication::send_packet_error()
{
    display_error(IDS_ERR_SENDPACKET, "Error sending packet");
}


bool CWACApplication::send_winamp_packet(PacketType type)
{
    EnPacket packet;
    packet.pack_byte(type);

    if(!send_packet(packet)) {
        send_packet_error();
        return false;
    }

    return true;
}
