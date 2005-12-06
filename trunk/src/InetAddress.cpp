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


#include <arpa/inet.h>
#include <cerrno>
#include <vector>

#include <frog/InetAddress.h>
#include <frog/NetworkInterface.h>

namespace frog
{
    namespace net
    {
        //--------------------------------------------------------------
        InetAddress::InetAddress() throw() 
            : addressFamily(addressFamily_),
            ipv4Compatible(ipv4Compatible_),
            ipv4Compatible_(true),
            index_(0),
            addressFamily_(AddressFamily::Unspecified)
            {
                memset(address_, 0, sizeof(uint8_t) * MAX_ADDR_SIZE);
            }

        //--------------------------------------------------------------
        InetAddress::InetAddress(const InetAddress& addr) throw()
            : addressFamily(addressFamily_), ipv4Compatible(ipv4Compatible_)
            {
                ::memcpy(address_, addr.address_, sizeof(uint8_t) * MAX_ADDR_SIZE);
                addressFamily_ = addr.addressFamily_;
                ipv4Compatible_ = addr.ipv4Compatible_;
                index_ = addr.index_;
            }

        //--------------------------------------------------------------
        InetAddress::InetAddress(const std::string& ipAddress, uint32_t index)
            throw(sys::IllegalArgumentException)
            : addressFamily(addressFamily_), ipv4Compatible(ipv4Compatible_)
            {
                // We know that it is not an IPv4 address if it contains
                // a semicolon.
                if(ipAddress.find(":") == std::string::npos)
                {
                    struct in_addr inaddr;
                    int res;
#ifdef HAVE_INET_PTON
                    res = ::inet_pton(AF_INET, ipAddress.c_str(), &inaddr);
#else
#ifdef HAVE_INET_ATON
                    res = ::inet_aton(ipAddress.c_str(), &inaddr);
#else // No choice but to use inet_addr
                    if((inaddr = ::inet_addr(ipAddress.c_str())) == -1)
                    {
                        res = 0;
                    }
#endif
#endif
                    if(res < 0)
                    {
                        throw sys::IllegalArgumentException(strerror(errno));
                    }
                    else if(res == 0)
                    {
                        throw sys::IllegalArgumentException("IP address is not valid.");
                    }

                    this->initIPv4(inaddr);
                    addressFamily_ = AddressFamily::InterNetwork;
                    ipv4Compatible_ = true;
                }
                else
                {
#ifdef HAVE_IPV6_SUPPORT
                    struct in6_addr in6addr;
#ifdef HAVE_INET_PTON
                    int res = ::inet_pton(AF_INET6, ipAddress.c_str(), &in6addr);
#else
#error	enabling IPv6 support without a working inet_pton(); configure without IPv6 support
#endif
                    if(res < 0)
                    {
                        throw sys::IllegalArgumentException(strerror(errno));
                    }
                    else if(res == 0)
                    {
                        throw sys::IllegalArgumentException("IP address is not valid.");
                    }

                    this->initIPv6(in6addr, index);
                    addressFamily_ = AddressFamily::InterNetworkV6;
                    ipv4Compatible_ = IN6_IS_ADDR_V4COMPAT(&in6addr);
#else
                    throw sys::IllegalArgumentException("IP address is not valid.");
#endif
                }
            }

        //--------------------------------------------------------------
        InetAddress::InetAddress(const struct in_addr& ipAddress)
            throw(sys::ArgumentOutOfBoundsException)
            : addressFamily(addressFamily_), ipv4Compatible(ipv4Compatible_)
            {
                this->initIPv4(ipAddress);
                addressFamily_ = AddressFamily::InterNetwork;
                ipv4Compatible_ = true;
            }

        //--------------------------------------------------------------
#ifdef HAVE_IPV6_SUPPORT
        InetAddress::InetAddress(const struct in6_addr& ipAddress, uint32_t index)
            throw(sys::ArgumentOutOfBoundsException)
            : addressFamily(addressFamily_), ipv4Compatible(ipv4Compatible_)
            {
                this->initIPv6(ipAddress, index);
                addressFamily_ = AddressFamily::InterNetworkV6;
                ipv4Compatible_ = IN6_IS_ADDR_V4COMPAT(&ipAddress);
            }
#endif

        //--------------------------------------------------------------
        InetAddress InetAddress::getLocalHost() throw(UnknownHostException)
        {
            std::vector<NetworkInterface>::iterator intfaceIter;
            std::vector<NetworkInterface> netInterfaces	= NetworkInterface::getNetworkInterfaces();
            NetworkInterface::InterfaceAddrList addrList;
            NetworkInterface::InterfaceAddrListIterator addrListIter;

            for(intfaceIter = netInterfaces.begin(); intfaceIter != netInterfaces.end();
                    ++intfaceIter)
            {
                addrList = intfaceIter->getInterfaceAddresses();
                for(addrListIter = addrList.begin(); addrListIter != addrList.end();
                        ++addrListIter)
                {
                    if(!addrListIter->unicast.isLoopbackAddress())
                    {
                        return addrListIter->unicast;
                    }
                }
            }
        }

        //--------------------------------------------------------------
        InetAddress::~InetAddress() throw()
        {
        }

        //--------------------------------------------------------------
        bool InetAddress::isAnyLocalAddress() throw()
        {
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                return((address_[IPV4_OFFSET + 0] == 0x00) && (address_[IPV4_OFFSET + 1] == 0x00) &&
                        (address_[IPV4_OFFSET + 2] == 0x00) && (address_[IPV4_OFFSET + 3] == 0x00));
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                uint8_t test = 0x00;
                for(int i= 0; i < MAX_ADDR_SIZE; ++i)
                {
                    test |= address_[i];
                }
                return (test == 0x00);
            }
#endif

            return false;
        }

        //--------------------------------------------------------------
        bool InetAddress::isLoopbackAddress() throw()
        {
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                return (address_[IPV4_OFFSET + 0] == 127U);
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                uint8_t test = 0x00;
                for(int i= 0; i < 15; ++i)
                {
                    test |= address_[i];
                }
                return ((test == 0x00) && (address_[15] == 0x01U));
            }
#endif

            return false;
        }

        //--------------------------------------------------------------
        bool InetAddress::isMulticastAddress() throw()
        {
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                return ((address_[IPV4_OFFSET + 0] & 0xf0) == 224U);
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                return ((address_[0] & 0xffU) == 0xffU);
            }
#endif
            return false;
        }

        //--------------------------------------------------------------
        bool InetAddress::isLinkLocalAddress() throw()
        {
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                return (((address_[IPV4_OFFSET + 0] & 0xffU) == 169U) &&
                        ((address_[IPV4_OFFSET + 1] & 0xffU) == 254U));
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                return (((address_[0] & 0xffU) == 0xfeU) &&
                        ((address_[1] & 0xc0U) == 0x80U));
            }
#endif
            return false;
        }

        //--------------------------------------------------------------
        bool InetAddress::isSiteLocalAddress() throw()
        {
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                return ((address_[IPV4_OFFSET + 0] & 0xffU) == 10U) ||
                    (((address_[IPV4_OFFSET + 0] & 0xffU) == 172U) &&
                     ((address_[IPV4_OFFSET + 1] & 0xffU) == 16U)) ||
                    (((address_[IPV4_OFFSET + 0] & 0xffU) == 192U) &&
                     ((address_[IPV4_OFFSET + 1] & 0xffU) == 168U));
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                return (((address_[0] & 0xffU) == 0xfeU) &&
                        ((address_[1] & 0xc0U) == 0xc0U));
            }
#endif
            return false;
        }

        //--------------------------------------------------------------
        bool InetAddress::isMulticastGlobal() throw()
        {
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                return (((address_[IPV4_OFFSET + 0] & 0xffU) >= 224U) &&
                        ((address_[IPV4_OFFSET + 0] & 0xffU) <= 238U)) &&
                    !(((address_[IPV4_OFFSET + 0] & 0xffU) == 224U) && 
                            ((address_[IPV4_OFFSET + 1] & 0xffU) == 0) &&
                            ((address_[IPV4_OFFSET + 2] & 0xffU) == 0));
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                return (((address_[0] & 0xffU) == 0xffU) &&
                        ((address_[1] & 0x0fU) == 0x0eU));
            }
#endif
            return false;
        }

        //--------------------------------------------------------------
        bool InetAddress::isMulticastNodeLocal() throw()
        {
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                // unless ttl == 0
                return false;
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                return (((address_[0] & 0xffU) == 0xffU) &&
                        ((address_[1] & 0x0fU) == 0x01U));
            }
#endif
            return false;
        }

        //--------------------------------------------------------------
        bool InetAddress::isMulticastLinkLocal() throw()
        {
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                return ((address_[IPV4_OFFSET + 0] & 0xffU) == 224U) &&
                    ((address_[IPV4_OFFSET + 1] & 0xffU) == 0) &&
                    ((address_[IPV4_OFFSET + 2] & 0xffU) == 0);
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                return (((address_[0] & 0xffU) == 0xffU) &&
                        ((address_[1] & 0x0fU) == 0x02U));
            }
#endif
            return false;
        }

        //--------------------------------------------------------------
        bool InetAddress::isMulticastSiteLocal() throw()
        {
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                return ((address_[IPV4_OFFSET + 0] & 0xffU) == 239U) &&
                    ((address_[IPV4_OFFSET + 1] & 0xffU) == 255U);
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                return (((address_[0] & 0xffU) == 0xffU) &&
                        ((address_[1] & 0x0fU) == 0x05U));
            }
#endif
            return false;
        }

        //--------------------------------------------------------------
        bool InetAddress::isMulticastOrgLocal() throw()
        {
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                return (((address_[IPV4_OFFSET + 0] & 0xffU) == 239U) &&
                        ((address_[IPV4_OFFSET + 1] & 0xffU) >= 192U) &&
                        ((address_[IPV4_OFFSET + 1] & 0xffU) <= 195U));
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                return (((address_[0] & 0xffU) == 0xffU) &&
                        ((address_[1] & 0x0fU) == 0x08U));
            }
#endif
            return false;
        }

        //--------------------------------------------------------------
        void InetAddress::getPrimitive(struct in_addr& rawIPAddress) const
        {
            ::memset(&rawIPAddress, 0, sizeof(struct in_addr));
            ::memcpy(&rawIPAddress.s_addr, address_ + IPV4_OFFSET, sizeof(uint8_t) * INADDRSZ);
        }

        //--------------------------------------------------------------
#ifdef HAVE_IPV6_SUPPORT
        void InetAddress::getPrimitive(struct in6_addr& rawIPAddress) const
        {
            ::memset(&rawIPAddress, 0, sizeof(struct in6_addr));
            ::memcpy(&rawIPAddress.s6_addr, address_, sizeof(uint8_t) * INADDRSZ6);
        }
#endif

        //--------------------------------------------------------------
        bool InetAddress::operator==(const InetAddress& addr) const throw()
        {
            return((!::memcmp(address_, addr.address_, sizeof(uint8_t) * MAX_ADDR_SIZE))
                    && (addressFamily == addr.addressFamily) && index_ == addr.index_);
        }

        //--------------------------------------------------------------
        bool InetAddress::operator!=(const InetAddress& addr) const throw()
        {
            return((::memcmp(address_, addr.address_, sizeof(uint8_t) * MAX_ADDR_SIZE))
                    || (addressFamily != addr.addressFamily) || (index_ != addr.index_));
        }
        //--------------------------------------------------------------
        InetAddress& InetAddress::operator=(const InetAddress& addr) throw()
        {
            if(this != &addr)
            {
                ::memcpy(address_, addr.address_, sizeof(uint8_t) * MAX_ADDR_SIZE);
                addressFamily_ = addr.addressFamily_;
                ipv4Compatible_ = addr.ipv4Compatible_;
                index_ = addr.index_;
            }
            return *this;
        }

        //--------------------------------------------------------------
        void InetAddress::initIPv4(const struct in_addr& ipAddress)
            throw(sys::ArgumentOutOfBoundsException)
            {
                if(ipAddress.s_addr > 0xFFFFFFFFU)
                {
                    throw sys::ArgumentOutOfBoundsException("IP address is out of range.");
                }

                uint8_t addr[MAX_ADDR_SIZE];
                ::memset(addr, 0, sizeof(uint8_t) * MAX_ADDR_SIZE);
                ::memcpy(addr, &ipAddress.s_addr, sizeof(ipAddress.s_addr));


                ::memset(address_, 0, sizeof(uint8_t) * MAX_ADDR_SIZE);
                ::memcpy(address_ + IPV4_OFFSET, &ipAddress.s_addr, sizeof(ipAddress.s_addr));

                index_ = 0;
            }

        //--------------------------------------------------------------
#ifdef HAVE_IPV6_SUPPORT
        void InetAddress::initIPv6(const struct in6_addr& ipAddress, uint32_t index)
            throw(sys::ArgumentOutOfBoundsException)
            {
                uint8_t addr[MAX_ADDR_SIZE];
                ::memset(addr, 0, sizeof(uint8_t) * MAX_ADDR_SIZE);
                ::memcpy(addr, &ipAddress.s6_addr, sizeof(ipAddress.s6_addr));

                for(int i= 0; i < MAX_ADDR_SIZE; ++i)
                {
                    if(addr[i] > 255U)
                        throw sys::ArgumentOutOfBoundsException("IP address is out of range.");
                }


                ::memset(address_, 0, sizeof(uint8_t) * MAX_ADDR_SIZE);
                ::memcpy(address_, &ipAddress.s6_addr, sizeof(ipAddress.s6_addr));

                index_ = index;
            }
#endif

        //--------------------------------------------------------------
        std::string InetAddress::getHostAddress() const throw()
        {
            std::string ipText = "";
            if(this->addressFamily == AddressFamily::InterNetwork)
            {
                char dst[INET_ADDRSTRLEN];
                struct in_addr inaddr;

                ::memset(dst, 0, sizeof(char) * INET_ADDRSTRLEN);
                ::memset(&inaddr, 0, sizeof(struct in_addr));

                ::memcpy(&inaddr.s_addr, address_ + IPV4_OFFSET, sizeof(uint8_t) * INADDRSZ);
#ifdef HAVE_INET_NTOP
                if((::inet_ntop(AF_INET, &inaddr,
                                dst, sizeof(char) * INET_ADDRSTRLEN) != NULL) && (dst != NULL))
                {
                    ipText = std::string(dst);
                }
#else
                ipText = std::string(inet_ntoa(inaddr));
#endif
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(this->addressFamily == AddressFamily::InterNetworkV6)
            {
                char dst[INET6_ADDRSTRLEN];
                struct in6_addr in6addr;

                ::memset(dst, 0, sizeof(char) * INET6_ADDRSTRLEN);
                ::memset(&in6addr, 0, sizeof(struct in6_addr));

                ::memcpy(&in6addr.s6_addr, address_, sizeof(uint8_t) * INADDRSZ6);

#ifdef HAVE_INET_NTOP
                if((::inet_ntop(AF_INET6, &in6addr,
                                dst, sizeof(char) * INET6_ADDRSTRLEN) != NULL) && (dst != NULL))
                {
                    std::string indexSuffix = "";
                    if(index_ != 0)
                    {
                        char indexTxt[3];
                        ::memset(indexTxt, 0, 3);
                        ::sprintf(indexTxt, "%d", index_);
                        indexSuffix = std::string("%") + std::string(indexTxt);
                    }
                    ipText = std::string(dst) + indexSuffix;
                }
#else
#error	enabling IPv6 support without a working inet_ntop(); configure without IPv6 support
#endif
            }
#endif

            return ipText;
        }

        //--------------------------------------------------------------
        std::string InetAddress::toString() const throw()
        {
            return getHostAddress();
        }

    } // net ns
} // frog ns
