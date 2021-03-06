/***************************************************************************
                          udpnet.cpp  -  Basic UDP/IP functionality
                             -------------------
    begin                : ma jan 17 2005
    copyright            : (C) 2005 by CJP
    email                : cornware-cjp@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <cstdio>
#include <cstdlib>

/*
Watch out with netinet/in.h: it contains definitions of
ntohl etc., and it should, but they conflict with other
declarations in system headers on some systems.
*/
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <unistd.h>

#include "udpnet.h"

CUDPNet::CUDPNet(unsigned int port)
{
	m_SendCounter = 0;

	m_Socket = socket(AF_INET,SOCK_DGRAM,0);
	if(m_Socket < 0)
	{
		printf("Cannot open socket\n");
		return;
	}

	int enable = 1;
	if(setsockopt(m_Socket, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(int)) != 0)
	{
		printf("Cannot use broadcast mode\n");
		close(m_Socket);
		m_Socket = -1;
		return;
	}

	// bind to port
	struct sockaddr_in MyAddress;
	MyAddress.sin_family = AF_INET;
	MyAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	MyAddress.sin_port = htons(port);

	int rc = bind (m_Socket, (struct sockaddr *) &MyAddress, sizeof(MyAddress));
	if(rc < 0)
	{
		printf("cannot bind port number %d \n", port);
		close(m_Socket);
		m_Socket = -1;
		return;
	}

	fcntl(m_Socket, F_SETFL, O_NONBLOCK);

	printf("Connected on port %d\n", port);
}

CUDPNet::~CUDPNet()
{
	closeConnection();
}

void CUDPNet::closeConnection()
{
	if(m_Socket >= 0) close(m_Socket);
	m_Socket = -1;
	printf("Disconnected\n");
}

bool CUDPNet::isConnected()
{
	return m_Socket >= 0;
}

bool CUDPNet::receiveData(unsigned int millisec)
{
	if(m_Socket < 0) return false;

	// Watch socket to see when it has input.
	struct pollfd pfd;
	pfd.fd = m_Socket;
	pfd.events = POLLIN;

	poll(&pfd, 1, millisec);
	if ((pfd.revents & POLLIN) == 0)
	{
		//printf("poll() says: no data on socket     \n");
		return false;
	}

	//DO NOT clear the data!!!
	//m_ReceivedData.clear();

	struct sockaddr_in caddr;
	socklen_t clen = sizeof(caddr);

	int len = 4096; //just for testing purposes. TODO: scan for MTU size (man ip(7))
	Uint8 buffer[len];

	//Receive:
	while(true)
	{
	    // receive message
		int n = recvfrom(m_Socket, (NETTYPE *)buffer, len, 0, (struct sockaddr *) &caddr, &clen);

		if(n < 0) //nothing received
			break;

		CIPNumber ipnum;
		ipnum = caddr.sin_addr.s_addr;
		int portnr = ntohs(caddr.sin_port);

		CBinBuffer binbuffer;
		for(unsigned int i=0; i < (unsigned int)n; i++)
			binbuffer.push_back(Uint8(buffer[i]));

		m_ReceiveBuffer.push_back(CMessageBuffer());
		CMessageBuffer &msgbuf = m_ReceiveBuffer.back();
		msgbuf.setBuffer(binbuffer);
		msgbuf.setIP(ipnum);
		msgbuf.setPort(portnr);
	}

	return true;
}

bool CUDPNet::sendData(CMessageBuffer &data)
{
	if(m_Socket < 0) return false;

	//printf("Sending %s\n", data.dump().c_str());

	data.setCounter(m_SendCounter);
	m_SendCounter++;

	CIPNumber ipnum = data.getIP();

	Uint8 num8[4];
	for(unsigned int i=0; i<4; i++)
		num8[i] = ipnum[i];
	Uint32 num32;
	memcpy(&num32, num8, sizeof(num32));

	//printf("Sending to %d.%d.%d.%d port %d\n", num8[0], num8[1], num8[2], num8[3], data.getPort());

	struct in_addr a;
	a.s_addr = num32;

	struct sockaddr_in remoteCliAddr;
	remoteCliAddr.sin_family = AF_INET;
	remoteCliAddr.sin_addr = a;
	remoteCliAddr.sin_port = htons(data.getPort());

	unsigned int len = data.size();
	Uint8 buffer[len];
	for(unsigned int i=0; i < len; i++)
		buffer[i] = data[i];

	int rc = sendto(m_Socket, (NETTYPE *)buffer, len,0 ,
		(struct sockaddr *) &remoteCliAddr,
		sizeof(remoteCliAddr));

	return (rc >= 0);
}

CIPNumber getBroadcastAddress()
{
	CIPNumber ret;
	ret = INADDR_BROADCAST;

	printf("Broadcast address is %s\n", ret.toString().c_str());

	return ret;
}
