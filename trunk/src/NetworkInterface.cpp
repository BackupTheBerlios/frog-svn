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

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif

#ifdef HAVE_SYS_SOCKIO_H
#include <sys/sockio.h>
#endif

#include <netinet/in.h>
#include <net/if.h>
#include <algorithm>
#include <cerrno>

#include <frog/nullptr.h>
#include <frog/NetworkInterface.h>

namespace frog
{
    namespace net
    {
        //--------------------------------------------------------------
        // Helper predicate
        class intfacenm_equal
        {
          public:
              intfacenm_equal(const std::string name)
                  : intfacenm_(name) { }
              bool operator()(const NetworkInterface intface)
              {
                  return (intfacenm_ == intface.name);
              }
          private:
              std::string intfacenm_;
        };


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
                intfaceIndex_ = netInterface.intfaceIndex_;
            }

        //--------------------------------------------------------------
        NetworkInterface& NetworkInterface::operator=(const NetworkInterface& netInterface) throw()
        {
            if(this != &netInterface)
            {
                name_ = netInterface.name_;
                displayName_ = netInterface.displayName_;
                addressList_ = netInterface.addressList_;
                intfaceIndex_ = netInterface.intfaceIndex_;
            }
            return *this;
        }

        //--------------------------------------------------------------
        bool NetworkInterface::operator==(const NetworkInterface& netInterface) const throw()
        {
            return ((name_ == netInterface.name_) &&
                    (addressList_ == netInterface.addressList_) &&
                    (intfaceIndex_ == netInterface.intfaceIndex_));
        }

        //--------------------------------------------------------------
        bool NetworkInterface::operator!=(const NetworkInterface& netInterface) const throw()
        {
            return ((name_ != netInterface.name_) ||
                    (!(addressList_ == netInterface.addressList_) ||
                     (intfaceIndex_ != netInterface.intfaceIndex_)));
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
#ifdef HAVE_IFADDRS_H
                NetworkInterface netInterface;
                struct ifaddrs* intfaceAddr;

                if(::getifaddrs(&intfaceAddr) == -1)
                {
                    throw SocketException(::strerror(errno));
                }

                InetAddress* addr_p      = NULL;
                InetAddress* netmask_p   = NULL;
                InetAddress* broadcast_p = NULL;
                uint32_t interfaceIndex = 0;

                while(intfaceAddr)
                {
                    if((intfaceAddr->ifa_addr->sa_family != AF_INET) 
#ifdef HAVE_IPV6_SUPPORT
                            && (intfaceAddr->ifa_addr->sa_family != AF_INET6)
#endif
                            || ((intfaceAddr->ifa_flags & IFF_UP) == 0) // Ignore if interface is not up
                            || (!(intfaceAddr->ifa_addr))) // Ignore if we do not have an IP address
                    {
                        intfaceAddr = intfaceAddr->ifa_next;
                        continue;
                    }

                    interfaceIndex = if_nametoindex(intfaceAddr->ifa_name);

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
#ifdef HAVE_IPV6_SUPPORT
                    else if(intfaceAddr->ifa_addr->sa_family == AF_INET6)
                    {
                        struct sockaddr_in6* sockaddr6;

                        sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_addr);
                        addr_p = new InetAddress(sockaddr6->sin6_addr, interfaceIndex);

                        if(intfaceAddr->ifa_netmask)
                        {
                            sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_netmask);
                            netmask_p = new InetAddress(sockaddr6->sin6_addr);
                        }

                        if(intfaceAddr->ifa_broadaddr)
                        {
                            sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_broadaddr);
                            broadcast_p = new InetAddress(sockaddr6->sin6_addr);
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

                        netInterface.intfaceIndex_ = interfaceIndex;

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
#else
                // No ::getifaddrs()
                int sockfd;
                int len, lastLen, flags;
                char* buf = frog::nullptr;
                char* ptr = frog::nullptr;
                struct ifconf ifc;
                struct ifreq* ifr;
                struct ifreq ifrcopy;
                struct sockaddr_in* sinptr;

                NetworkInterface netInterface;
                uint32_t interfaceIndex = 0;

                if((sockfd = ::socket(AF_INET, SOCK_DGRAM, 0)) == -1)
                {
                    throw SocketException(::strerror(errno));
                }

                lastLen = 0;
                len = 100 * sizeof(struct ifreq); // Initial buffer guess
                for(;;)
                {
                    buf = new char[len];
                    ifc.ifc_len = len;
                    ifc.ifc_buf = buf;
                    if(::ioctl(sockfd, SIOCGIFCONF, &ifc) < 0)
                    {
                        if(errno != EINVAL || lastLen != 0)
                        {
                            delete[] buf;
                            buf = frog::nullptr;
                            throw SocketException(::strerror(errno));
                        }
                    }
                    else
                    {
                        if(ifc.ifc_len == lastLen)
                            break; // Success, len has not changed
                        lastLen = ifc.ifc_len;
                    }
                    len  += 10 * sizeof(struct ifreq); // Increment
                    delete[] buf;
                    buf = frog::nullptr;
                }

                InetAddress* addr_p = NULL;
                InetAddress* netmask_p = NULL;
                InetAddress* broadcast_p = NULL;

                for(ptr = buf; ptr < buf + ifc.ifc_len; )
                {
                    ifr = reinterpret_cast<struct ifreq*>(ptr);
                    switch(ifr->ifr_addr.sa_family)
                    {
                      case AF_INET:
                          len = sizeof(struct sockaddr);
                          break;
                      default:
                          break;
                    }
                    ptr += sizeof(ifr->ifr_name) + len; // For next one in buffer

                    if(ifr->ifr_addr.sa_family != AF_INET)
                        continue;

                    ifrcopy = *ifr;
                    if((::ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy)) == -1)
                    {
                        throw SocketException(::strerror(errno));
                    }
                    flags = ifrcopy.ifr_flags;
                    if((flags & IFF_UP) == 0)
                        continue; // Ignore if interface is not up

                    sinptr = reinterpret_cast<struct sockaddr_in*>(&ifr->ifr_addr);
                    addr_p = new InetAddress(sinptr->sin_addr);

                    if((::ioctl(sockfd, SIOCGIFNETMASK, &ifrcopy)) == -1)
                    {
                        throw SocketException(::strerror(errno));
                    }
#if defined(__linux__)
                    sinptr = reinterpret_cast<struct sockaddr_in*>(&ifrcopy.ifr_netmask);
#else
                    sinptr = reinterpret_cast<struct sockaddr_in*>(&ifrcopy.ifr_enaddr);
#endif
                    netmask_p = new InetAddress(sinptr->sin_addr);

                    if(flags & IFF_BROADCAST)
                    {
                        if((::ioctl(sockfd, SIOCGIFBRDADDR, &ifrcopy)) == -1)
                        {
                            throw SocketException(::strerror(errno));
                        }
                        sinptr = reinterpret_cast<struct sockaddr_in*>(&ifrcopy.ifr_broadaddr);
                        broadcast_p = new InetAddress(sinptr->sin_addr);
                    }

                    if((::ioctl(sockfd, SIOCGIFINDEX, &ifrcopy)) == -1)
                    {
                        throw SocketException(::strerror(errno));
                    }

#if defined(__linux__)
                    interfaceIndex = ifrcopy.ifr_ifindex;
#else
                    interfaceIndex = ifrcopy.ifr_index;
#endif

                    bool addrMatch = false;
                    bool nameMatch = false;

                    if(addr)
                        addrMatch = (*addr_p == *addr);
                    if(name.length() > 0)
                        nameMatch = (name == std::string(ifr->ifr_name));

                    if(addrMatch || nameMatch)
                    {
                        netInterface.name_ = std::string(ifr->ifr_name);
                        netInterface.displayName_ = std::string(ifr->ifr_name);

                        NetworkInterface::InterfaceAddress addrs;
                        memset(&addrs, 0, sizeof(NetworkInterface::InterfaceAddress));

                        addrs.unicast = *addr_p;

                        if(netmask_p) 
                            addrs.netmask = *netmask_p;
                        if(broadcast_p)
                            addrs.broadcast = *broadcast_p;

                        netInterface.intfaceIndex_ = interfaceIndex;

                        netInterface.addressList_.push_back(addrs);
                    }

                    if(addr_p)
                    {
                        delete addr_p;
                        addr_p =NULL;
                    }

                    if(netmask_p)
                    {
                        delete netmask_p;
                        netmask_p =NULL;
                    }

                    if(broadcast_p)
                    {
                        delete broadcast_p;
                        broadcast_p =NULL;
                    }
                }
                delete[] buf;
                buf = frog::nullptr;

                return netInterface;
#endif
            }

        //--------------------------------------------------------------
        std::vector<NetworkInterface> NetworkInterface::findAll() throw(SocketException)
        {
#ifdef HAVE_IFADDRS_H
            std::vector<NetworkInterface> netInterfaces;
            std::vector<NetworkInterface>::iterator intfaceIter;
            struct ifaddrs* intfaceAddr;

            if(::getifaddrs(&intfaceAddr) == -1)
            {
                throw SocketException(::strerror(errno));
            }

            InetAddress* addr_p      = NULL;
            InetAddress* netmask_p   = NULL;
            InetAddress* broadcast_p = NULL;
            uint32_t interfaceIndex = 0;

            while(intfaceAddr)
            {
                if((intfaceAddr->ifa_addr->sa_family != AF_INET) 
#ifdef HAVE_IPV6_SUPPORT
                        && (intfaceAddr->ifa_addr->sa_family != AF_INET6)
#endif
                        || ((intfaceAddr->ifa_flags & IFF_UP) == 0) // Ignore if interface is not up
                        || (!(intfaceAddr->ifa_addr))) // Ignore if we do not have an IP address
                {
                    intfaceAddr = intfaceAddr->ifa_next;
                    continue;
                }

                interfaceIndex = if_nametoindex(intfaceAddr->ifa_name);

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
#ifdef HAVE_IPV6_SUPPORT
                else if(intfaceAddr->ifa_addr->sa_family == AF_INET6)
                {
                    struct sockaddr_in6* sockaddr6;

                    sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_addr);
                    addr_p = new InetAddress(sockaddr6->sin6_addr, interfaceIndex);

                    if(intfaceAddr->ifa_netmask)
                    {
                        sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_netmask);
                        netmask_p = new InetAddress(sockaddr6->sin6_addr);
                    }

                    if(intfaceAddr->ifa_broadaddr)
                    {
                        sockaddr6 = reinterpret_cast<struct sockaddr_in6*>(intfaceAddr->ifa_broadaddr);
                        broadcast_p = new InetAddress(sockaddr6->sin6_addr);
                    }
                }
#endif
                NetworkInterface netInterface;
                NetworkInterface::InterfaceAddress addrs;

                memset(&addrs, 0, sizeof(NetworkInterface::InterfaceAddress));

                addrs.unicast = *addr_p;

                if(netmask_p) 
                    addrs.netmask = *netmask_p;
                if(broadcast_p)
                    addrs.broadcast = *broadcast_p;

                intfaceIter = std::find_if(netInterfaces.begin(), 
                        netInterfaces.end(), intfacenm_equal(std::string(intfaceAddr->ifa_name)));

                if(intfaceIter == netInterfaces.end())
                {
                    netInterface.name_ = std::string(intfaceAddr->ifa_name);
                    netInterface.displayName_ = std::string(intfaceAddr->ifa_name);

                    netInterface.intfaceIndex_ = interfaceIndex;

                    netInterface.addressList_.push_back(addrs);
                    netInterfaces.push_back(netInterface);
                }
                else
                {
                    intfaceIter->addressList_.push_back(addrs);
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

            return netInterfaces;
#else
            // No ::getifaddrs()
            int sockfd;
            int len, lastLen, flags;
            char* buf = frog::nullptr;
            char* ptr = frog::nullptr;
            struct ifconf ifc;
            struct ifreq* ifr;
            struct ifreq ifrcopy;
            struct sockaddr_in* sinptr;

            std::vector<NetworkInterface> netInterfaces;
            std::vector<NetworkInterface>::iterator intfaceIter;

            uint32_t interfaceIndex = 0;

            if((sockfd = ::socket(AF_INET, SOCK_DGRAM, 0)) == -1)
            {
                throw SocketException(::strerror(errno));
            }

            lastLen = 0;
            len = 100 * sizeof(struct ifreq); // Initial buffer guess
            for(;;)
            {
                buf = new char[len];
                ifc.ifc_len = len;
                ifc.ifc_buf = buf;
                if(::ioctl(sockfd, SIOCGIFCONF, &ifc) < 0)
                {
                    if(errno != EINVAL || lastLen != 0)
                    {
                        delete[] buf;
                        buf = frog::nullptr;
                        throw SocketException(::strerror(errno));
                    }
                }
                else
                {
                    if(ifc.ifc_len == lastLen)
                        break; // Success, len has not changed
                    lastLen = ifc.ifc_len;
                }
                len  += 10 * sizeof(struct ifreq); // Increment
                delete[] buf;
                buf = frog::nullptr;
            }

            InetAddress* addr_p = NULL;
            InetAddress* netmask_p = NULL;
            InetAddress* broadcast_p = NULL;

            for(ptr = buf; ptr < buf + ifc.ifc_len; )
            {
                ifr = reinterpret_cast<struct ifreq*>(ptr);
                switch(ifr->ifr_addr.sa_family)
                {
                  case AF_INET:
                      len = sizeof(struct sockaddr);
                      break;
                  default:
                      break;
                }
                ptr += sizeof(ifr->ifr_name) + len; // For next one in buffer

                if(ifr->ifr_addr.sa_family != AF_INET)
                    continue;

                ifrcopy = *ifr;
                if((::ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy)) == -1)
                {
                    throw SocketException(::strerror(errno));
                }
                flags = ifrcopy.ifr_flags;
                if((flags & IFF_UP) == 0)
                    continue; // Ignore if interface is not up

                sinptr = reinterpret_cast<struct sockaddr_in*>(&ifr->ifr_addr);
                addr_p = new InetAddress(sinptr->sin_addr);

                if((::ioctl(sockfd, SIOCGIFNETMASK, &ifrcopy)) == -1)
                {
                    throw SocketException(::strerror(errno));
                }
#if defined(__linux__)
                sinptr = reinterpret_cast<struct sockaddr_in*>(&ifrcopy.ifr_netmask);
#else
                sinptr = reinterpret_cast<struct sockaddr_in*>(&ifrcopy.ifr_enaddr);
#endif
                netmask_p = new InetAddress(sinptr->sin_addr);

                if(flags & IFF_BROADCAST)
                {
                    if((::ioctl(sockfd, SIOCGIFBRDADDR, &ifrcopy)) == -1)
                    {
                        throw SocketException(::strerror(errno));
                    }
                    sinptr = reinterpret_cast<struct sockaddr_in*>(&ifrcopy.ifr_broadaddr);
                    broadcast_p = new InetAddress(sinptr->sin_addr);
                }

                if((::ioctl(sockfd, SIOCGIFINDEX, &ifrcopy)) == -1)
                {
                    throw SocketException(::strerror(errno));
                }

#if defined(__linux__)
                interfaceIndex = ifrcopy.ifr_ifindex;
#else
                interfaceIndex = ifrcopy.ifr_index;
#endif

                NetworkInterface netInterface;
                NetworkInterface::InterfaceAddress addrs;

                memset(&addrs, 0, sizeof(NetworkInterface::InterfaceAddress));

                addrs.unicast = *addr_p;

                if(netmask_p) 
                    addrs.netmask = *netmask_p;
                if(broadcast_p)
                    addrs.broadcast = *broadcast_p;
                intfaceIter = std::find_if(netInterfaces.begin(), 
                        netInterfaces.end(), intfacenm_equal(std::string(ifr->ifr_name)));

                if(intfaceIter == netInterfaces.end())
                {
                    netInterface.name_ = std::string(ifr->ifr_name);
                    netInterface.displayName_ = std::string(ifr->ifr_name);

                    netInterface.intfaceIndex_ = interfaceIndex;

                    netInterface.addressList_.push_back(addrs);
                    netInterfaces.push_back(netInterface);
                }
                else
                {
                    intfaceIter->addressList_.push_back(addrs);
                }

                if(addr_p)
                {
                    delete addr_p;
                    addr_p =NULL;
                }

                if(netmask_p)
                {
                    delete netmask_p;
                    netmask_p =NULL;
                }

                if(broadcast_p)
                {
                    delete broadcast_p;
                    broadcast_p =NULL;
                }
            }
            delete[] buf;
            buf = frog::nullptr;

            return netInterfaces;
#endif
        }

        //--------------------------------------------------------------
        std::string NetworkInterface::toString() const throw()
        {

            char indexTxt[3];
            ::memset(indexTxt, 0, 3);
            ::sprintf(indexTxt, "%d", intfaceIndex_);

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
                    (broadcast == other.broadcast));
        }

        //--------------------------------------------------------------
        bool NetworkInterface::InterfaceAddress::operator!=(const InterfaceAddress& other) const throw()
        {
            return ((unicast != other.unicast) || (netmask != other.netmask) ||
                    (broadcast != other.broadcast));
        }
    } // net ns
} // frog ns
