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
#include <net/if.h>
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
			NetworkInterface::NetworkInterface(const NetworkInterface& netInterface) throw()
				: name(name_), displayName(displayName_)
			{
				name_ = netInterface.name_;
				displayName_ = netInterface.displayName_;
				addressList_ = netInterface.addressList_;
			}

			//--------------------------------------------------------------
			NetworkInterface& NetworkInterface::operator=(const NetworkInterface& netInterface) throw()
			{
				if(this != &netInterface)
				{
					name_ = netInterface.name_;
					displayName_ = netInterface.displayName_;
					addressList_ = netInterface.addressList_;
				}
				return *this;
			}

			//--------------------------------------------------------------
			bool NetworkInterface::operator==(const NetworkInterface& netInterface) const throw()
			{
				return ((name_ == netInterface.name_) &&
						(addressList_ == netInterface.addressList_));
			}

			//--------------------------------------------------------------
			bool NetworkInterface::operator!=(const NetworkInterface& netInterface) const throw()
			{
				return ((name_ != netInterface.name_) ||
						(!(addressList_ == netInterface.addressList_)));
			}

			//--------------------------------------------------------------
			std::vector<NetworkInterface> NetworkInterface::getNetworkInterfaces()
			{
				return NetworkInterface::findAll();
			}

			//--------------------------------------------------------------
			NetworkInterface::InterfaceAddrList NetworkInterface::getInterfaceAddresses() const
			{
				return addressList_;
			}

			//--------------------------------------------------------------
			NetworkInterface NetworkInterface::find(const InetAddress* addr, const std::string name)
				throw(SocketException)
			{
				NetworkInterface netInterface;
				struct ifaddrs* intfaceAddr;

				if(::getifaddrs(&intfaceAddr) == -1)
				{
					throw SocketException(strerror(errno));
				}

				InetAddress* addr_p      = NULL;
				InetAddress* netmask_p   = NULL;
				InetAddress* broadcast_p = NULL;

				while(intfaceAddr)
				{
					if(((intfaceAddr->ifa_addr->sa_family != AF_INET) &&
								(intfaceAddr->ifa_addr->sa_family != AF_INET6)) ||
							(!(intfaceAddr->ifa_addr)))
					{
						intfaceAddr = intfaceAddr->ifa_next;
						continue;
					}

					if(intfaceAddr->ifa_addr->sa_family == AF_INET)
					{
						struct sockaddr_in* sockaddr;

						sockaddr = reinterpret_cast<struct sockaddr_in*>(intfaceAddr->ifa_addr);
						addr_p = new InetAddress(sockaddr->sin_addr);

						if(intfaceAddr->ifa_netmask)
						{
							sockaddr = reinterpret_cast<struct sockaddr_in*>(intfaceAddr->ifa_netmask);
							netmask_p = new InetAddress(sockaddr->sin_addr);
						}

						if(intfaceAddr->ifa_broadaddr)
						{
							sockaddr = reinterpret_cast<struct sockaddr_in*>(intfaceAddr->ifa_broadaddr);
							broadcast_p = new InetAddress(sockaddr->sin_addr);
						}
					}
#if HAVE_IPV6_SUPPORT
					else if(intfaceAddr->ifa_addr->sa_family == AF_INET6)
					{
						struct sockaddr_in6* sockaddr6;

						sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_addr);
						addr_p = new InetAddress(sockaddr6->sin6_addr, if_nametoindex(intfaceAddr->ifa_name));

						if(intfaceAddr->ifa_netmask)
						{
							sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_netmask);
							netmask_p = new InetAddress(sockaddr6->sin6_addr, if_nametoindex(intfaceAddr->ifa_name));
						}

						if(intfaceAddr->ifa_broadaddr)
						{
							sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_broadaddr);
							broadcast_p = new InetAddress(sockaddr6->sin6_addr, if_nametoindex(intfaceAddr->ifa_name));
						}
					}
#endif

					bool addrMatch = false;
					bool nameMatch = false;

					if(addr)
						addrMatch = (*addr_p == *addr);
					if(name.length() > 0)
						nameMatch = (name == std::string(intfaceAddr->ifa_name));

					if(addrMatch || nameMatch)
					{
						netInterface.name_ = std::string(intfaceAddr->ifa_name);
						netInterface.displayName_ = std::string(intfaceAddr->ifa_name);

						NetworkInterface::InterfaceAddress addrs;
						memset(&addrs, 0, sizeof(NetworkInterface::InterfaceAddress));
						
						addrs.unicast = *addr_p;

						if(netmask_p) 
							addrs.netmask = *netmask_p;
						if(broadcast_p)
							addrs.broadcast = *broadcast_p;

						addrs.index = if_nametoindex(intfaceAddr->ifa_name);

						netInterface.addressList_.push_back(addrs);
					}

					if(addr_p)
					{
						delete addr_p;
						addr_p = NULL;
					}

					if(netmask_p)
					{
						delete netmask_p;
						netmask_p = NULL;
					}

					if(broadcast_p)
					{
						delete broadcast_p;
						broadcast_p = NULL;
					}

					intfaceAddr = intfaceAddr->ifa_next;
				}

				::freeifaddrs(intfaceAddr);

				return netInterface;
			}

			//--------------------------------------------------------------
			std::vector<NetworkInterface> NetworkInterface::findAll() throw(SocketException)
			{
				std::vector<NetworkInterface> netInterfaces;
				struct ifaddrs* intfaceAddr;

				if(::getifaddrs(&intfaceAddr) == -1)
				{
					throw SocketException(strerror(errno));
				}

				InetAddress* addr_p      = NULL;
				InetAddress* netmask_p   = NULL;
				InetAddress* broadcast_p = NULL;

				while(intfaceAddr)
				{
					if(((intfaceAddr->ifa_addr->sa_family != AF_INET) &&
								(intfaceAddr->ifa_addr->sa_family != AF_INET6)) ||
							(!(intfaceAddr->ifa_addr)))
					{
						intfaceAddr = intfaceAddr->ifa_next;
						continue;
					}

					if(intfaceAddr->ifa_addr->sa_family == AF_INET)
					{
						struct sockaddr_in* sockaddr;

						sockaddr = reinterpret_cast<struct sockaddr_in*>(intfaceAddr->ifa_addr);
						addr_p = new InetAddress(sockaddr->sin_addr);

						if(intfaceAddr->ifa_netmask)
						{
							sockaddr = reinterpret_cast<struct sockaddr_in*>(intfaceAddr->ifa_netmask);
							netmask_p = new InetAddress(sockaddr->sin_addr);
						}

						if(intfaceAddr->ifa_broadaddr)
						{
							sockaddr = reinterpret_cast<struct sockaddr_in*>(intfaceAddr->ifa_broadaddr);
							broadcast_p = new InetAddress(sockaddr->sin_addr);
						}
					}
#if HAVE_IPV6_SUPPORT
					else if(intfaceAddr->ifa_addr->sa_family == AF_INET6)
					{
						struct sockaddr_in6* sockaddr6;

						sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_addr);
						addr_p = new InetAddress(sockaddr6->sin6_addr, if_nametoindex(intfaceAddr->ifa_name));

						if(intfaceAddr->ifa_netmask)
						{
							sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_netmask);
							netmask_p = new InetAddress(sockaddr6->sin6_addr, if_nametoindex(intfaceAddr->ifa_name));
						}

						if(intfaceAddr->ifa_broadaddr)
						{
							sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_broadaddr);
							broadcast_p = new InetAddress(sockaddr6->sin6_addr, if_nametoindex(intfaceAddr->ifa_name));
						}
					}
#endif
					NetworkInterface netInterface;
					NetworkInterface::InterfaceAddress addrs;
					
					netInterface.name_ = std::string(intfaceAddr->ifa_name);
					netInterface.displayName_ = std::string(intfaceAddr->ifa_name);

					memset(&addrs, 0, sizeof(NetworkInterface::InterfaceAddress));
					addrs.unicast = *addr_p;

					if(netmask_p) 
						addrs.netmask = *netmask_p;
					if(broadcast_p)
						addrs.broadcast = *broadcast_p;

					addrs.index = if_nametoindex(intfaceAddr->ifa_name);

					netInterface.addressList_.push_back(addrs);
					netInterfaces.push_back(netInterface);

					if(addr_p)
					{
						delete addr_p;
						addr_p = NULL;
					}

					if(netmask_p)
					{
						delete netmask_p;
						netmask_p = NULL;
					}

					if(broadcast_p)
					{
						delete broadcast_p;
						broadcast_p = NULL;
					}

					intfaceAddr = intfaceAddr->ifa_next;
				}

				::freeifaddrs(intfaceAddr);

				return netInterfaces;
			}
			
			//--------------------------------------------------------------
			std::string NetworkInterface::toString() const throw()
			{
				char indexTxt[3];
				::memset(indexTxt, 0, 3);
				::sprintf(indexTxt, "%d", addressList_[0].index);
				
				std::string niTxt= std::string("name: ") + name_ + std::string(" (") + 
					displayName_ + std::string(")  index: ") + std::string(indexTxt)+ std::string("  addresses: ");
				
				std::string addressesTxt = "";
				for(int i = 0; i != addressList_.size(); ++i)
				{
					addressesTxt += (addressList_[i].unicast.getHostAddress() + "; ");
				}

				return (niTxt + addressesTxt);
			}

			//--------------------------------------------------------------
			bool NetworkInterface::InterfaceAddress::operator==(const InterfaceAddress& other) const throw()
			{
				return ((unicast == other.unicast) && (netmask == other.netmask) &&
						(broadcast == other.broadcast) && (index == other.index));
			}

			//--------------------------------------------------------------
			bool NetworkInterface::InterfaceAddress::operator!=(const InterfaceAddress& other) const throw()
			{
				return ((unicast != other.unicast) || (netmask != other.netmask) ||
						(broadcast != other.broadcast) || (index != other.index));
			}
		} // net ns
	} // sys ns
} // frog ns
