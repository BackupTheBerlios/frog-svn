// C++ implementation file -----------------------------------------------//
//   Frog Framework - A useful framework for C++ applications.
//   Copyright (C) 2005 by Janvier D. Anonical <janvier@users.berlios.de>
//
//   This library is free software; you can redistribute it and/or
//   modify it under the terms of the GNU Lesser General Public
//   License as published by the Free Software Foundation; either
//   version 2.1 of the License, or (at your option) any later version.
//
//   This library is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   Lesser General Public License for more details.
//
//   You should have received a copy of the GNU Lesser General Public
//   License along with this library; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
//   MA  02110-1301  USA
//------------------------------------------------------------------------//


#include <sys/socket.h>

#include <frog/AddressFamily.h>

namespace frog
{
	namespace sys
	{
		namespace net
		{
			//-----------------------------------------------------------------------
			const sa_family_t AddressFamily::Unspecified = AF_UNSPEC;
			const sa_family_t AddressFamily::Local = AF_LOCAL;
			const sa_family_t AddressFamily::Unix = AF_UNIX;
			const sa_family_t AddressFamily::File = AF_FILE;
			const sa_family_t AddressFamily::InterNetwork = AF_INET;
			const sa_family_t AddressFamily::Ax25 = AF_AX25;
			const sa_family_t AddressFamily::Ipx = AF_IPX;
			const sa_family_t AddressFamily::AppleTalk = AF_APPLETALK;
			const sa_family_t AddressFamily::NetRom = AF_NETROM;
			const sa_family_t AddressFamily::Bridge = AF_BRIDGE;
			const sa_family_t AddressFamily::AtmPvc = AF_ATMPVC;
			const sa_family_t AddressFamily::X25 = AF_X25;
#ifdef HAVE_IPV6_SUPPORT
			const sa_family_t AddressFamily::InterNetworkV6 = AF_INET6;
#endif
			const sa_family_t AddressFamily::Rose = AF_ROSE;
			const sa_family_t AddressFamily::DecNet =  AF_DECnet;
			const sa_family_t AddressFamily::NetBeui = AF_NETBEUI;
			const sa_family_t AddressFamily::Security = AF_SECURITY;
			const sa_family_t AddressFamily::Key = AF_KEY;
			const sa_family_t AddressFamily::NetLink = AF_NETLINK;
			const sa_family_t AddressFamily::Route = AF_ROUTE;
			const sa_family_t AddressFamily::Packet = AF_PACKET;
			const sa_family_t AddressFamily::Ash = AF_ASH;
			const sa_family_t AddressFamily::EcoNet = AF_ECONET;
			const sa_family_t AddressFamily::AtmSvc = AF_ATMSVC;
			const sa_family_t AddressFamily::Sna = AF_SNA;
			const sa_family_t AddressFamily::Irda = AF_IRDA;
			const sa_family_t AddressFamily::Pppox = AF_PPPOX;
			const sa_family_t AddressFamily::WanPipe = AF_WANPIPE;
			const sa_family_t AddressFamily::BlueTooth = PF_BLUETOOTH;
		} // net ns
	} // sys ns
} // frog ns
