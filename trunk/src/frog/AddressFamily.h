// C++ header file -------------------------------------------------------//
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


#ifndef FROG_SYS_NET_ADDRESSFAMILY_H
#define FROG_SYS_NET_ADDRESSFAMILY_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/socket.h>

#include <frog/Object.h>

/**
 * @namespace frog The Frog Framework is library of C++ classes,
 * interfaces, and value types.
 */
namespace frog
{
	/**
	 * @namespace frog::net Provides a simple programming
	 * interface for many of the protocols used on networking
	 * applications.
	 */
	namespace net
	{
		/**
		 * Specifies addressing schemes that the framework will use.
		 */
		class AddressFamily : public Object
		{
		  public:
			  typedef sa_family_t TYPE; /**< The type of an AddressFamily */
#if defined(__linux__)
			  static const sa_family_t Unspecified; /**< Unspecified address family. */
			  static const sa_family_t Local; /**< Local to host (pipes and file-domain). */
			  static const sa_family_t Unix; /**< Same as AddressFamily::Local. */
			  static const sa_family_t File;  /**< Same as AddressFamily::Local. */
			  static const sa_family_t InterNetwork; /**< IP version 4 */
			  static const sa_family_t Ax25; /**< Amateur Radio AX.25. */
			  static const sa_family_t Ipx; /**< Novell Internet Protocol. */
			  static const sa_family_t AppleTalk; /**< Appletalk DDP. */
			  static const sa_family_t NetRom; /**< Amateur radio NetROM. */
			  static const sa_family_t Bridge; /**< Multiprotocol bridge. */
			  static const sa_family_t AtmPvc; /**< ATM PVCs. */
			  static const sa_family_t X25; /**< Reserved for X.25 project. */
#ifdef HAVE_IPV6_SUPPORT
			  static const sa_family_t InterNetworkV6; /**< IP version 6. */
#endif
			  static const sa_family_t Rose; /**< Amateur Radio X.25 PLP. */
			  static const sa_family_t DecNet; /**< Reserved for DECnet project. */
			  static const sa_family_t NetBeui; /**< Reserved for 802.2LLC project. */
			  static const sa_family_t Security; /**< Security callback pseudo AF. */
			  static const sa_family_t Key; /**< Key management API. */
			  static const sa_family_t NetLink; /**< NetLink address family */
			  static const sa_family_t Route; /**< Alias to emulate 4.4BSD. */
			  static const sa_family_t Packet; /**< Packet family. */
			  static const sa_family_t Ash; /**< Ash address family. */
			  static const sa_family_t EcoNet; /**< Acorn Econet. */
			  static const sa_family_t AtmSvc; /**< ATM SVCs. */
			  static const sa_family_t Sna; /**< Linux SNA Project. */
			  static const sa_family_t Irda; /**< IRDA sockets. */
			  static const sa_family_t Pppox; /**< PPPoX sockets. */
			  static const sa_family_t WanPipe; /**< Wanpipe API sockets. */
			  static const sa_family_t BlueTooth; /**< BlueTooth sockets. */
			  static const sa_family_t Max; /**< Max address family */
#elif defined(__sun__)			
			  static const sa_family_t Unspecified; /**< Unspecified address family. */
			  static const sa_family_t Unix; /**< Local to host (pipes and file-domain). */
			  static const sa_family_t InterNetwork; /**< IP version 4 */
			  static const sa_family_t ImpLink; /**< Arpanet imp address */
			  static const sa_family_t Pup; /**< Pup protocols: e.g. BSP */
			  static const sa_family_t Chaos; /**< mit CHAOS protocols */
			  static const sa_family_t Ns; /**< XEROX NS protocols */
			  static const sa_family_t Nbs; /**< Nbs protocols */
			  static const sa_family_t Ecma; /**< European computer manufacturers */
			  static const sa_family_t DataKit; /**< Datakit protocols */
			  static const sa_family_t Ccitt; /**< CCITT protocols, X.25 etc. */
			  static const sa_family_t Sna; /**< IBM SNA */
			  static const sa_family_t DecNet; /**< DecNet */
			  static const sa_family_t Dli; /**< Direct data link interface */
			  static const sa_family_t Lat; /**< LAT */
			  static const sa_family_t HyLink; /**< NSC Hyperchannel */
			  static const sa_family_t AppleTalk; /**< Appletalk DDP. */
			  static const sa_family_t Nit; /**< Network Interface Tap */
			  static const sa_family_t Iso8802; /**< IEEE 802.2, also ISO 8802 */
			  static const sa_family_t Osi; /**< Umbrella for all families used */
			  static const sa_family_t X25; /**< CCITT X.25 in particular */
			  static const sa_family_t OsiNet; /**< AFI =47, IDI = 4 */
			  static const sa_family_t Gosip; /**< U.S. Government OSI */
			  static const sa_family_t Ipx; /**< Novell Internet Protocol */
			  static const sa_family_t Route; /**< Internal Routing Protocol */
			  static const sa_family_t Link; /**< Link-layer interface */
#ifdef HAVE_IPV6_SUPPORT
			  static const sa_family_t InterNetworkV6; /**< IP version 6. */
#endif
			  static const sa_family_t Key; /**< Security Association DB sicjet */
			  static const sa_family_t Nca; /**< NCA socket */

			  static const sa_family_t Max; /**< Max address family */
#else
#error platform not supported
#endif
		}; // AddressFamily cls
	} // net ns
} // frog ns

using frog::net::AddressFamily;

#endif // FROG_SYS_NET_ADDRESSFAMILY_H
