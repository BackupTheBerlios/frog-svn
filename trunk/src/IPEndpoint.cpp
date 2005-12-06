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
#include <sstream>

#include <frog/IPEndpoint.h>

namespace frog
{
    namespace net
    {
        //--------------------------------------------------------------
        IPEndpoint::IPEndpoint(InetAddress& ipAddress, in_port_t portNo) throw()
            : address(ipAddress), port(portNo)
            {
                setAddressFamily(ipAddress.addressFamily);
            }

        //--------------------------------------------------------------
        IPEndpoint& IPEndpoint::operator=(const IPEndpoint& ep) throw()
        {
            if(this != &ep)
            {
                address = ep.address;
                port = ep.port;
                setAddressFamily(ep.address.addressFamily);
            }
            return *this;
        }

        //--------------------------------------------------------------
        bool IPEndpoint::operator==(const IPEndpoint& ep) const throw()
        {
            return ((address == ep.address) && (port == ep.port)
                    && (addressFamily == ep.addressFamily));
        }

        //--------------------------------------------------------------
        bool IPEndpoint::operator!=(const IPEndpoint& ep) const throw()
        {

            return ((address != ep.address) || (port != ep.port)
                    || (addressFamily != ep.addressFamily));
        }

        //--------------------------------------------------------------
        std::string IPEndpoint::toString() const throw()
        {
            std::ostringstream portStr;
            portStr << port;
            std::string ipEndpointStr = "";

            if(addressFamily == AddressFamily::InterNetwork)
            {
                ipEndpointStr = address.toString() + ":" + portStr.str();
            }
#ifdef HAVE_IPV6_SUPPORT
            else if(addressFamily == AddressFamily::InterNetworkV6)
            {
                ipEndpointStr = "[" + address.toString() + "]:" + portStr.str();
            }
#endif

            return ipEndpointStr;
        }
    } // net ns
} // frog ns
