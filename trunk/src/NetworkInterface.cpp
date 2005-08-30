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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#ifdef HAVE_IFADDRS_H
#include <ifaddrs.h>
#endif

#include <netinet/in.h>
#include <cerrno>

#include <frog/NetworkInterface.h>

namespace frog
{
	namespace sys
	{
		namespace net
		{
			//--------------------------------------------------------------
			NetworkInterface NetworkInterface::getByInetAddress(const InetAddress& addr)
				throw(SocketException)
			{
				return NetworkInterface::find(&addr);
			}
			
			//--------------------------------------------------------------
			NetworkInterface NetworkInterface::getByName(const std::string& intfaceName)
				throw(SocketException)
			{
				return NetworkInterface::find(NULL, intfaceName);
			}
			
			//--------------------------------------------------------------
			NetworkInterface::~NetworkInterface() throw()
			{
			}

			//--------------------------------------------------------------
			std::vector<NetworkInterface> NetworkInterface::getNetworkInterfaces()
			{
			}

			//--------------------------------------------------------------
			std::vector<InetAddress> NetworkInterface::getInetAddresses() const
			{
				return addresses_;
			}
			
			//--------------------------------------------------------------
			NetworkInterface NetworkInterface::find(const InetAddress* addr, const std::string name)
				throw(SocketException)
			{
				NetworkInterface netInterface ;
				struct ifaddrs* intfaceAddr;

				if(::getifaddrs(&intfaceAddr) == -1)
				{
					throw SocketException(strerror(errno));
				}

				InetAddress* inetAddr_p = NULL;
				while(intfaceAddr)
				{
					if(intfaceAddr->ifa_addr->sa_family == AF_INET)
					{
						struct sockaddr_in* sockaddr = reinterpret_cast<struct sockaddr_in*>(intfaceAddr->ifa_addr);
						inetAddr_p = new InetAddress(sockaddr->sin_addr);
					}
#if HAVE_IPV6_SUPPORT
					else if(intfaceAddr->ifa_addr->sa_family == AF_INET6)
					{
						struct sockaddr_in6* sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_addr);
						inetAddr_p = new InetAddress(sockaddr6->sin6_addr, sockaddr6->sin6_scope_id);
					}
#endif
					else
					{
						intfaceAddr = intfaceAddr->ifa_next;
						continue;
					}

					bool addrMatch = false;
					bool nameMatch = false;

					if(addr != NULL)
						addrMatch = (*inetAddr_p == *addr);
					if(name.length() > 0)
						nameMatch = (name == std::string(intfaceAddr->ifa_name));

					if(addrMatch || nameMatch)
					{
						netInterface.name_ = std::string(intfaceAddr->ifa_name);
						netInterface.displayName_ = std::string(intfaceAddr->ifa_name);
						netInterface.addresses_.push_back(*inetAddr_p);
					}

					intfaceAddr = intfaceAddr->ifa_next;
				}

				::freeifaddrs(intfaceAddr);
				if(inetAddr_p)
				{
					delete inetAddr_p;
				}
				else
				{
					throw SocketException();
				}
				
				return netInterface;
			}
		} // net ns
	} // sys ns
} // frog ns
