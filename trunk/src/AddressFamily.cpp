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
    namespace net
    {
        //-----------------------------------------------------------------------
#if defined(__linux__)
        const sa_family_t AddressFamily::Unspecified = AF_UNSPEC;
        const sa_family_t AddressFamily::Unix = AF_UNIX;
        const sa_family_t AddressFamily::Local = AF_UNIX;
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

        const sa_family_t AddressFamily::Max = AF_MAX;
#elif defined(__sun__)
        const sa_family_t AddressFamily::Unspecified = AF_UNSPEC;
        const sa_family_t AddressFamily::Unix = AF_UNIX;
        const sa_family_t AddressFamily::InterNetwork = AF_INET;
        const sa_family_t AddressFamily::ImpLink = AF_IMPLINK;
        const sa_family_t AddressFamily::Pup = AF_PUP;
        const sa_family_t AddressFamily::Chaos = AF_CHAOS;
        const sa_family_t AddressFamily::Ns = AF_NS;
        const sa_family_t AddressFamily::Nbs = AF_NBS;
        const sa_family_t AddressFamily::Ecma = AF_ECMA;
        const sa_family_t AddressFamily::DataKit = AF_DATAKIT;
        const sa_family_t AddressFamily::Ccitt = AF_CCITT;
        const sa_family_t AddressFamily::Sna = AF_SNA;
        const sa_family_t AddressFamily::DecNet =  AF_DECnet;
        const sa_family_t AddressFamily::Dli = AF_DLI;
        const sa_family_t AddressFamily::Lat = AF_LAT;
        const sa_family_t AddressFamily::HyLink = AF_HYLINK;
        const sa_family_t AddressFamily::AppleTalk = AF_APPLETALK;
        const sa_family_t AddressFamily::Nit = AF_NIT;
        const sa_family_t AddressFamily::Iso8802 = AF_802;
        const sa_family_t AddressFamily::Osi = AF_OSI;
        const sa_family_t AddressFamily::X25 = AF_X25;
        const sa_family_t AddressFamily::OsiNet = AF_OSINET;
        const sa_family_t AddressFamily::Gosip = AF_GOSIP;
        const sa_family_t AddressFamily::Ipx = AF_IPX;
        const sa_family_t AddressFamily::Route = AF_ROUTE;
        const sa_family_t AddressFamily::Link = AF_LINK;
#ifdef HAVE_IPV6_SUPPORT
        const sa_family_t AddressFamily::InterNetworkV6 = AF_INET6;
#endif
        const sa_family_t AddressFamily::Key = AF_KEY;
        const sa_family_t AddressFamily::Nca = AF_NCA;

        const sa_family_t AddressFamily::Max = AF_MAX;
#else
#error platform not supported
#endif
    } // net ns
} // frog ns
